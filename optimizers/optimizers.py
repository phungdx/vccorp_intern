"""
Author: Phung Dao.
"""

import numpy as np
import matplotlib.pyplot as plt
import viz # My visualization functions.


class GradientDescentLinearRegression:
    """
    Linear Regression with gradient-based optimization.
    Parameters
    ----------
    learning_rate : float
        Learning rate for the gradient descent algorithm.
    max_iterations : int
        Maximum number of iteration for the gradient descent algorithm.
    eps : float
        Tolerance level for the Euclidean norm between model parameters in two 
        consequitive iterations. The algorithm is stopped when the norm becomes 
        less than the tolerance level.
    """
    
    def __init__(self, learning_rate=0.01, max_iterations=100000, eps=1e-6):
        self.learning_rate = learning_rate
        self.max_iterations = max_iterations
        self.eps = eps
        
    def predict(self, X):
        """Returns predictions array of shape [n_samples,1]"""
        return np.dot(X, self.w.T)
    
    def cost(self, X, y):
        """Returns the value of the cost function as a scalar real number"""
        y_pred = self.predict(X)
        loss = (y - y_pred)**2
        return np.mean(loss)

    def grad(self, X, y):
        """Returns the gradient vector"""
        y_pred = self.predict(X)
        d_intercept = -2*sum(y - y_pred)                    # dJ/d w_0.
        d_x = -2*sum(X[:,1:] * (y - y_pred).reshape(-1,1))  # dJ/d w_i.
        g = np.append(np.array(d_intercept), d_x)           # Gradient.
        return g / X.shape[0]                               # Average over training samples.

    def adagrad(self, g):
        self.G += g**2                                     # Update cache.
        step = self.learning_rate / (np.sqrt(self.G + self.eps)) * g
        return step


    def rmsprop(self, g):
        self.G += 0.9*self.G +  0.1*g**2                                     # Update cache.
        step = self.learning_rate / (np.sqrt(self.G + self.eps)) * g
        return step

    def adam(self, g, iter):
        self.m = 0.9*self.m + 0.1*g
        self.v = 0.999*self.v + (1 - 0.999)*(g**2)
        m_hat = self.m / (1 - 0.9**(iter+1))
        v_hat = self.v / (1 - 0.999**(iter + 1))
        step = self.learning_rate*m_hat / (np.sqrt(v_hat) + self.eps)
        return step
        
    def fit(self, X, y, method = "standard", verbose = True):
        """
        Fit linear model with gradient descent.
        
        Parameters
        ----------
        X : numpy array or sparse matrix of shape [n_samples,n_predictors]
            Training data
        y : numpy array of shape [n_samples,1]
            Target values.
        method : string
                 Defines the variant of gradient descent to use. 
                 Possible values: "standard", "adagrad".
        verbose: boolean
                 If True, print the gradient, parameters and the cost function 
                 for each iteration.
        
        Returns
        -------
        self : returns an instance of self.
        """
        
        self.w = np.zeros(X.shape[1])                     # Initialization of params.
        if method in ["adagrad", "rmsprop"]:
            self.G = np.zeros(X.shape[1])                 # Initialization of cache for AdaGrad.
        if method  == "adam":
            self.m = np.zeros(X.shape[1])
            self.v = np.zeros(X.shape[1])
        w_hist = [self.w]                                 # History of params.
        cost_hist = [self.cost(X, y)]                     # History of cost.      
        
        for iter in range(self.max_iterations):
            
            g = self.grad(X, y)                           # Calculate the gradient.
            if method == "standard":
                step = self.learning_rate * g             # Calculate standard gradient step.
            elif method == "adagrad":
                step = self.adagrad(g)                    # Calculate AdaGrad step.
            elif method == "rmsprop":
                step = self.rmsprop(g)
            elif method == "adam":
                step = self.adam(g, iter)
            else:
                raise ValueError("Method not supported.")
            self.w = self.w - step                        # Update parameters.
            w_hist.append(self.w)                         # Save to history.
            
            J = self.cost(X, y)                           # Calculate the cost.
            cost_hist.append(J)                           # Save to history.
            
            if verbose:
                print(f"Iter: {iter}, gradient: {g}, params: {self.w}, cost: {J}")
            
            # Stop if update is small enough.
            if np.linalg.norm(w_hist[-1] - w_hist[-2]) < self.eps:
                break
        
        # Final updates before finishing.
        self.iterations = iter + 1                       # Due to zero-based indexing.
        self.w_hist = w_hist
        self.cost_hist = cost_hist
        self.method = method
        
        return self

# Simple alternative to adaptive alpha is self.learning_rate = 1 / (iter + self.eps)
            
def generate_data(n_predictors = 1, n_samples = 100, location = 1, scale = 3):
    """Generate data for the linear regression"""
    
    # Reproducibility.
    np.random.seed(6)     
    # True parameters, +1 for the intercept.
    w_star = np.random.randn(n_predictors + 1)
    X = np.random.normal(loc = location, 
                         scale = scale, 
                         size = (n_samples, n_predictors))
    # Add a column of ones for an intercept.   
    X = np.column_stack((np.ones(n_samples), X))
    noise = np.random.randn(n_samples)
    # Compute output variable.
    y = np.dot(X, w_star.T) + noise
    
    return X, y


if __name__ == "__main__":

    LR = 1
    MAX_ITER = 100
    METHOD = "adam"


    path = "./"

    X, y = generate_data()

    model = GradientDescentLinearRegression(LR, MAX_ITER).fit(X, y, METHOD)
    print(f"Gradient descent solution in {model.iterations} iterations: {model.w}.")

    w_lstsq = np.linalg.lstsq(X, y, rcond = None)[0]
    print(f"Least squares solutions: {w_lstsq}.")

    if (X.shape[1] == 2):
        # Generate plots only for a two-parameter problem.
        
        viz.plot_data(X, y)
        # plt.savefig(path + "1-generated-data.png")

        viz.plot_data_and_fitted_line(X, y, model)
        # plt.savefig(path + "2-generated-data-and-fitted-line.png")
        
        viz.plot_cost(model)
        # plt.savefig(path + "3-cost-hist.png")
        
        # Animation plot ------------------------------------------------------
        
        iter_dict = {("standard", 0.001): 50,
                     ("standard", 0.015): 20,
                     ("standard", 0.05): 20,
                     ("standard", 0.08): 15,
                     ("adagrad", 1): 11}
        
        viz.animate_fitted_line(X, y, model, path, iterations = iter_dict.get((METHOD, LR), 20))

        # Surface plot -------------------------------------------------------
                
        surf_dict = {("standard", 0.001): {"steps": len(model.w_hist), 
                                           "annotation_steps": 5,
                                           "title": f"Path of the converging gradient descent with $\\alpha$={LR}"},
                     ("standard", 0.015): {"steps": len(model.w_hist), 
                                           "annotation_steps": 5,
                                           "title": f"Path of the converging gradient descent with $\\alpha$={LR}"},
                     ("standard", 0.05): {"steps": len(model.w_hist), 
                                           "annotation_steps": 5,
                                           "title": f"Path of the converging gradient descent with $\\alpha$={LR}"},
                     ("standard", 0.08): {"steps": 7, 
                                           "annotation_steps": 7,
                                           "title": f"Path of the diverging gradient descent with $\\alpha$={LR}"},
                     ("adagrad", 1): {"steps": len(model.w_hist), 
                                           "annotation_steps": 3,
                                           "title": f"AdaGrad with $\\eta$={LR}"}}
        
        surf_dict_default = {"steps": 5, "annotation_steps": 5, "title": ""}
        
        viz.plot_surface(X, y, model, path, params = surf_dict.get((METHOD, LR), surf_dict_default))




# # Experiment with two mathematically equivalent versions of AdaGrad.
# g = np.array([1, 5])
# eta = 1 # 0.01
# eps = 0 # 1e-6

# # V1: Element-wise.
# G = np.zeros(g.shape)
# G += g**2
# lr = eta / (np.sqrt(G + eps))
# step = lr * g
# print(f"g: {g}, G: {G}, learning rate: {lr}, step: {step}")

# # V2: Matrix.
# G = np.zeros((g.shape[0], g.shape[0]))
# G += np.outer(g,g)
# diag_G = np.diag(G)
# lr = np.diag(eta / np.sqrt(diag_G + eps))
# step = lr @ g
# print(f"g: {g}, G: {G}, learning rate: {lr}, step: {step}")