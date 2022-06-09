'''
Xác suất để 1 vector x thuộc class c: p(c|x)
c = argmax(c) p(c|x) = argmax(c) p(x|c)p(c)
p(c): xác suất để 1 điểm rơi vào class c, có thể được tính bằng MLE(maximum likelihood estimation) hoặc MAP estimation 
p(x|c): phân phối các điểm dữ liệu trong class c, thường rất khó tính toán vì x có nhiều chiều, vì vậy giả sử rằng
các thành phần của x độc lẫn nhau

Tóm tắt:
- Naive Bayes Classifiers (NBC) thường được sử dụng trong các bài toán Text Classification.
- NBC có thời gian training và test rất nhanh.
Điều này có được là do giả sử về tính độc lập giữa các thành phần, nếu biết class.
- Nếu giả sử về tính độc lập được thoả mãn (dựa vào bản chất của dữ liệu),
NBC được cho là cho kết quả tốt hơn so với SVM và logistic regression khi có ít dữ liệu training.
- NBC có thể hoạt động với các feature vector mà một phần là liên tục (sử dụng Gaussian Naive Bayes),
phần còn lại ở dạng rời rạc (sử dụng Multinomial hoặc Bernoulli).
- Khi sử dụng Multinomial Naive Bayes, Laplace smoothing thường được sử dụng
để tránh trường hợp 1 thành phần trong test data chưa xuất hiện ở training data.
'''

# from __future__ import print_function
# from sklearn.naive_bayes import BernoulliNB
# import numpy as np 

# # train data
# d1 = [1, 1, 1, 0, 0, 0, 0, 0, 0]
# d2 = [1, 1, 0, 1, 1, 0, 0, 0, 0]
# d3 = [0, 1, 0, 0, 1, 1, 0, 0, 0]
# d4 = [0, 1, 0, 0, 0, 0, 1, 1, 1]

# train_data = np.array([d1, d2, d3, d4])
# label = np.array(['B', 'B', 'B', 'N']) # 0 - B, 1 - N 

# # test data
# d5 = np.array([[1, 0, 0, 1, 0, 0, 0, 1, 0]])
# d6 = np.array([[0, 1, 0, 0, 0, 0, 0, 1, 1]])

# ## call MultinomialNB
# clf = BernoulliNB()
# # training 
# clf.fit(train_data, label)

# # test
# print('Predicting class of d5:', str(clf.predict(d5)[0]))
# print('Probability of d6 in each class:', clf.predict_proba(d6))



# ----------------------------------------------------------

# from sklearn.naive_bayes import MultinomialNB
# import numpy as np 

# # train data
# d1 = [2, 1, 1, 0, 0, 0, 0, 0, 0]
# d2 = [1, 1, 0, 1, 1, 0, 0, 0, 0]
# d3 = [0, 1, 0, 0, 1, 1, 0, 0, 0]
# d4 = [0, 1, 0, 0, 0, 0, 1, 1, 1]

# train_data = np.array([d1, d2, d3, d4])
# label = np.array(['B', 'B', 'B', 'N']) 

# # test data
# d5 = np.array([[2, 0, 0, 1, 0, 0, 0, 1, 0]])
# d6 = np.array([[0, 1, 0, 0, 0, 0, 0, 1, 1]])

# ## call MultinomialNB
# clf = MultinomialNB()
# # training 
# clf.fit(train_data, label)

# # test
# print('Predicting class of d5:', str(clf.predict(d5)[0]))
# print('Probability of d6 in each class:', clf.predict_proba(d5))


# ---------------------------------------------------------------------------

## packages 
from __future__ import division, print_function, unicode_literals
import numpy as np
from scipy.sparse import coo_matrix # for sparse matrix
from sklearn.naive_bayes import MultinomialNB, BernoulliNB
from sklearn.metrics import accuracy_score # for evaluating results

# data path and file name 
train_data_fn = 'train-features-50.txt'
test_data_fn = 'test-features.txt'
train_label_fn = 'train-labels-50.txt'
test_label_fn = 'test-labels.txt'

nwords = 2500 

def read_data(data_fn, label_fn):
    ## read label_fn
    with open(label_fn) as f:
        content = f.readlines()
    label = [int(x.strip()) for x in content]

    ## read data_fn
    with open(data_fn) as f:
        content = f.readlines()
    # remove '\n' at the end of each line
    content = [x.strip() for x in content] 

    dat = np.zeros((len(content), 3), dtype = int)
    
    for i, line in enumerate(content): 
        a = line.split(' ')
        dat[i, :] = np.array([int(a[0]), int(a[1]), int(a[2])])
    
    # remember to -1 at coordinate since we're in Python
    # check this: https://docs.scipy.org/doc/scipy/reference/generated/scipy.sparse.coo_matrix.html
    # for more information about coo_matrix function 
    data = coo_matrix((dat[:, 2], (dat[:, 0] - 1, dat[:, 1] - 1)),\
             shape=(len(label), nwords))
    return (data, label)

(train_data, train_label)  = read_data(train_data_fn, train_label_fn)
(test_data, test_label)  = read_data(test_data_fn, test_label_fn)

clf = MultinomialNB()
# clf = BernoulliNB()
clf.fit(train_data, train_label)

y_pred = clf.predict(test_data)
print('Training size = %d, accuracy = %.2f%%' % \
      (train_data.shape[0],accuracy_score(test_label, y_pred)*100))