from matplotlib.image import imread
import numpy as np
import matplotlib.pyplot as plt
import os
plt.rcParams['figure.figsize'] = [12, 8]
plt.rcParams.update({'font.size': 18})

A = imread(os.path.join('D:\\Workspace\\intern\\vccorp\\image_processing\\point_operators\\forest.jpeg'))
B = np.mean(A, -1); # Convert RGB to grayscale

Bt = np.fft.fft2(B)
Btsort = np.sort(np.abs(Bt.reshape(-1))) # sort by magnitude

# Zero out all small coefficients and inverse transform
for keep in (0.1, 0.05, 0.01, 0.005):
    thresh = Btsort[int(np.floor((1-keep)*len(Btsort)))] 
    ind = np.abs(Bt)>thresh          # Find small indices
    Btlow = Bt * ind                 # Threshold small indices
    Alow = np.fft.ifft2(Btlow).real  # Compressed image
    plt.figure()
    plt.imshow(Alow,cmap='gray')
    # plt.savefig(f'{keep}.jpeg')
    plt.axis('off')
    plt.title('Compressed image: keep = ' + str(keep))


plt.show()