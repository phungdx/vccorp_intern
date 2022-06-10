# -*- coding: utf-8 -*-
"""
@author: Phung Dao
"""
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm       # Color legend for the surface plot.
from celluloid import Camera    # Animation.


def plot_data(X, y):
    """"2D scatter plot of generated data."""
    fig, ax = plt.subplots(figsize = (4, 3), dpi = 100)
    ax.scatter(X[:,1], y, color = "blue", label='Generated data')
    ax.legend()
    plt.xlabel("x")
    plt.ylabel("y")

def plot_data_and_fitted_line(X, y, model):
    """"2D scatter plot of generated data and a fitted line."""
    
    fig, ax = plt.subplots(figsize = (4, 3), dpi = 100)
    ax.plot(X[:,1], model.predict(X), color = "red", label='Fitted line')
    ax.scatter(X[:,1], y, color = "blue", label='Generated data')
    ax.legend()
    plt.xlabel("x")
    plt.ylabel("y")

def plot_cost(model):
    """2D plot of the cost on each iteration."""
    fig, ax = plt.subplots(figsize = (4, 3), dpi = 100)
    ax.plot(model.cost_hist, color = "blue", label = "Cost")
    ax.legend()
    plt.xlabel("iteration")
    plt.ylabel("$J(\mathbf{w})$")
   
def animate_fitted_line(X, y, model, path, iterations):
    """
    Animation of the fitted line.
    Source: https://github.com/jwkvam/celluloid
    """

    fig, ax = plt.subplots(figsize=(5, 4), dpi=100)
    plt.xlabel("x")
    plt.ylabel("y")
    
    camera = Camera(fig)
    for i in range(iterations):
        ax.scatter(X[:,1], y, color = "blue")
        w = model.w_hist[i]
        y_pred = np.dot(X, w.T)
        t = ax.plot(X[:,1], y_pred, color = "red")
        plt.legend(t, [f"Iter. {i}, line equation: {w[0]:.3f}+{w[1]:.3f}x"], loc = 'upper left')
        camera.snap()   
        
    animation = camera.animate()
    # animation.save(f"{path}animation-method-{model.method}-lr-{model.learning_rate}.gif", writer = 'imagemagick')

def plot_surface(X, y, model, path, params):
    """
    3D plot of the cost function. 
    Source: https://matplotlib.org/2.0.2/mpl_toolkits/mplot3d/tutorial.html
    """
    
    n_steps = params["steps"]
    fig_title = params["title"]
    annotation_steps = params["annotation_steps"]
    x_lo, x_hi = -2, 2    
    
    # Plot parameters depending on the learning rate.
    if (model.learning_rate == 0.08):
        # Divergence.
        y_lo, y_hi = -13, 13
    else:
        # Convergence.
        y_lo, y_hi = -0.05, 0.84*2
        
    
    # Plot quality.
    # Source: https://stackoverflow.com/questions/332289/how-do-you-change-the-size-of-figures-drawn-with-matplotlib
    # and https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.figure.html
    fig = plt.figure(figsize = (10, 5), dpi = 100)   
    ax = fig.gca(projection = '3d')
    ax.set_title(fig_title)
    ax.set_xlabel('$w_0$')
    ax.set_ylabel('$w_1$')
    ax.set_zlabel('$J(\mathbf{w})$')
    ax.view_init(30, 20) # Rotate the coordinate system.
    
    
    x_space = np.linspace(x_lo, x_hi, 100)
    y_space = np.linspace(y_lo, y_hi, 100)
    x_mesh, y_mesh = np.meshgrid(x_space, y_space)
    z = np.zeros(x_mesh.shape)
    
    def cost(X, y, w):
        y_pred = np.dot(X, w.T)
        loss = (y - y_pred)**2
        return np.mean(loss)
    
    for i in range(len(x_space)):
        for j in range(len(y_space)):
            z[i,j] = cost(X, y, np.array([x_mesh[i,j], y_mesh[i,j]]))
    
    # Plot the surface.
    surf = ax.plot_surface(x_mesh, y_mesh, z,
                           cmap = cm.coolwarm, 
                           linewidth = 0, 
                           antialiased = True, 
                           vmin = 0, 
                           rcount = 300,
                           alpha = 0.6)
    
    
    # Add points for cost function value on each iteration -------------------

    # Source: https://matplotlib.org/stable/tutorials/toolkits/mplot3d.html#scatter-plots    
    x_space = np.array(model.w_hist)[:, 0]
    y_space = np.array(model.w_hist)[:, 1]
    z = np.array(model.cost_hist)
        
    ax.scatter(x_space[:n_steps], 
               y_space[:n_steps], 
               z[:n_steps], 
               s = 10,
               color = "red", 
               alpha = 1)
    
    
    x_arrow_end = np.diff(x_space[:n_steps])
    y_arrow_end = np.diff(y_space[:n_steps])
    z_arrow_end = np.diff(z[:n_steps])
    
    annotations = [f"$w^{({i})}$" for i in range(annotation_steps)] # Number of steps to display.
    for i, txt in enumerate(annotations):
         ax.text(x_space[i] - 0.1, y_space[i], z[i], txt, fontsize = 8, color = "red", alpha = 1)
    
    # Add arrows -------------------------------------------------------------
    
    # Source: https://matplotlib.org/stable/tutorials/toolkits/mplot3d.html#quiver   
    ax.quiver(x_space[:(n_steps-1)],
              y_space[:(n_steps-1)],
              z[:(n_steps-1)],
              x_arrow_end,
              y_arrow_end,
              z_arrow_end,
              arrow_length_ratio = 0,
              color = "red", 
              alpha = 1)
    
    # Export the plot.
    # plt.savefig(path + f"{path}surface-method-{model.method}-lr-{model.learning_rate}.png", dpi = 300)
    
    # Add a color bar which maps values to colors.
    fig.colorbar(surf, shrink=0.5, aspect=5)
    
    plt.show()