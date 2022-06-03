import cv2
import numpy as np
from PIL import Image
import math
import matplotlib.pyplot as plt

def distance_pixels():
	# Generating desired test image with red and green dot at desired locations
	# Black 28x28 image
	image = np.zeros((28,28,3), np.uint8)

	# Choose red pixel location
	image[10,15] = [0,0,255]

	# Choose green pixel location
	image[21,23] = [0,255,0]

	# Save image
	cv2.imwrite('1.png', image)

	# Finding distance between the pixels
	x1,y1,x2,y2 = 10,15,21,23
	print("Distance : ", math.sqrt((x2-x1)**2 + (y2-y1)**2))


def image_negatives():
	img = cv2.imread('dog_color.jpeg')
	L = img.max()
	print(L)
	new_img = L - img
	cv2.imshow('inverted_img.jpg', new_img)
	cv2.waitKey(0)
	cv2.destroyAllWindows()


def gamma_correction():

	img = cv2.imread('dog_color.jpeg')

	# Sample gamma values to test
	for gamma in [0.2, 0.5, 1, 1.5, 1.8]:
    	# Apply gamma correction.
		gamma_transformation = np.array(255*(img / 255) ** gamma, dtype = 'uint8')
		cv2.imwrite('gamma_transformed'+str(gamma)+'.jpg', gamma_transformation)

	cv2.waitKey(0)
	cv2.destroyAllWindows()


def Contrast_stretch():

	def Contrast_stretch_(p, r1, s1, r2, s2):

	    if (0 <= p and p <= r1):
	        equation = (s1 / r1) * p
	    elif (r1 < p and p <= r2):
	        equation = ((s2 - s1) / (r2 - r1)) * (p - r1) + s1
	    else:
	        equation = ((255 - s2) / (255 - r2)) * (p - r2) + s2
	    return equation

	img = cv2.imread('dog_color.jpeg')

	# Initialize range
	r1 = 55
	s1 = 40
	r2 = 140
	s2 = 200

	pixelVal_vec = np.vectorize(Contrast_stretch_)
  
	# Contrast stretching
	contrast = pixelVal_vec(img, r1, s1, r2, s2)

	cv2.imwrite('contrast.jpg', contrast)


def grey_slicing():
	#  Img is a grey scale image
	img = cv2.imread('dog_color.jpeg', 0)

	#  Find width and height of image
	row, column = img.shape

	#  Create an zeros array to store the sliced image
	img1 = np.zeros((row, column), dtype = 'uint8')

	#  Specify the min and max range
	min_range = 80
	max_range = 140

	# Loop over the input image and if pixel value lies in desired range set it to 255 
	# otherwise set it to desired value
	for i in range(row):
	    for j in range(column):
	        if img[i,j] > min_range and img[i,j] < max_range: 
	            img1[i,j] = 255
	        else: 
	            img1[i,j] = img[i-1, j-1] 

	# cv2.imwrite('Original.jpg', img)
	cv2.imwrite('slicedimage.jpg', img1)
	cv2.waitKey(0)
	cv2.destroyAllWindows()



'''
Neighborhood operations
'''

def padding(img):
	img2 = cv2.resize(img, (256,256))

	# Make black border
	image = cv2.copyMakeBorder(img2, 2, 2, 2, 2, cv2.BORDER_CONSTANT, None, value = 0)
	 
	print('New dimensions', image.shape[0], 'X', image.shape[1])

	return image


def avg_neighbor():
	# Creating a copy for traversing original values and updating in new matrix

	img = cv2.imread('dog_color.jpeg')
	padded_img = padding(img)
	img2 = padded_img.copy()
	for i in range(2, 258):
	    for j in range(2, 258):
	        
	        # for a 5x5 window sliding
	        vector_sum = 0
	        n = 0
	        # Fetch all neighbours for middle element of a 5x5 matrix
	        for k in range(i - 2, i + 3):
	            for l in range(j - 2, j + 3):
	                n += 1
	                #Calculate sum of 
	                vector_sum += padded_img[k, l].astype(int)
	        #Finding average of neigbours, excluding centre element
	        vector_mean = (vector_sum - padded_img[i, j]) / (n - 1)
	        img2[i, j] = vector_mean

	cv2.imwrite('average_neighbor_operation.jpg', img2)
	cv2.waitKey(0)
	cv2.destroyAllWindows()


def minimum_neighbor():
	img = cv2.imread('dog_color.jpeg')
	padded_img = padding(img)
	# Creating a copy for traversing original values and updating in new matrix
	img2 = padded_img.copy()
	# Traverse image portions alone
	for i in range(2,258):
	    for j in range(2,258):
	        # for a 5x5 window sliding
	        neighbors = []
	        # Fetch all neighbours for middle element of a 5x5 matrix
	        for k in range(i-2,i+3):
	            for l in range(j-2,j+3):
	                neighbors.append(padded_img[k,l])

	        minimum = np.min(neighbors, axis=0)
	        img2[i, j] = minimum


	cv2.imwrite('minimum_neighbor_operation.jpg', img2)


# Arithmetic Operations
def addition():
	img1 = cv2.imread('image1.png')
	img2 = cv2.imread('image2.png')

	# Resize to 640 x 480
	img1_resize = cv2.resize(img1, (640,480))
	img2_resize = cv2.resize(img2, (640,480))

	cv2.imshow('as1',img1_resize)
	cv2.imshow('as2',img2_resize)

	# Addition operation
	imgAdd = cv2.addWeighted(img1_resize, 0.5, img2_resize, 0.5, 0)

	cv2.imshow('result', imgAdd)
	cv2.waitKey(0)
	cv2.destroyAllWindows()


def division():
	img1 = cv2.imread('image1.png')
	img2 = cv2.imread('image2.png')

	# Resize to 640 x 480
	img1_resize = cv2.resize(img1, (640,480))
	img2_resize = cv2.resize(img2, (640,480))

	# Image 1 / Image 2
	img1Img2 = cv2.divide(img1_resize, img2_resize)
	cv2.imshow('1',img1Img2)

	# Image 2 / Image 1
	img2Img1 = cv2.divide(img2_resize, img1_resize)
	cv2.imshow('2',img2Img1)

	cv2.waitKey(0)
	cv2.destroyAllWindows()


def xor_not():

	img1 = cv2.imread('image1.png')
	img2 = cv2.imread('image2.png')

	# Resize to 640 x 480
	img1_resize = cv2.resize(img1, (640,480))
	img2_resize = cv2.resize(img2, (640,480))

	# Bitwise XOR
	img_xor = cv2.bitwise_xor(img1_resize, img2_resize, mask = None)

	# Bitwise NOT
	img_not = cv2.bitwise_not(img1_resize, img2_resize, mask = None)

	cv2.imshow('1', img_xor)
	cv2.imshow('2', img_not)

	cv2.waitKey(0)
	cv2.destroyAllWindows()


def rotation():
	# Read image
	img = cv2.imread('image1.png')

	# Dimensions of image
	ht, wt, c = img.shape

	# Get centre coordinates
	Center_X, Center_Y = (wt//2, ht//2)

	# Define angle of rotation
	angle = 90

	# Rotation around center of image
	# parameters of getRotationMatrix2D - Center coordinates, angle of rotation in degrees, image scale
	rot_matrix = cv2.getRotationMatrix2D((Center_X, Center_Y), angle, 1.0)
	rotate = cv2.warpAffine(img, rot_matrix, (wt, ht))

	cv2.imshow('rotated', rotate)

	cv2.waitKey(0)
	cv2.destroyAllWindows()


def affine():
	# Read image
	img = cv2.imread('image1.png')

	# Dimensions of image
	ht, wt, c = img.shape

	# Get source and destination coordinates
	src_pts = np.float32([[50,50],
	                     [200,50],
	                     [50,200]])

	dst_pts = np.float32([[10,100],
	                     [200,50],
	                     [100,250]])
	 
	# Set Affine matrix
	matrix = cv2.getAffineTransform(src_pts, dst_pts)

	# Transform
	affine = cv2.warpAffine(img, matrix, (wt, ht))


	cv2.imshow('affine', affine)

	cv2.waitKey(0)
	cv2.destroyAllWindows()


def statistics():
	# Read image
	img = cv2.imread('image1.png')

	# Mean 
	mean = np.mean(img)

	# Variance 
	variance = np.var(img)

	print('Mean: ', mean)
	print('Variance: ', variance)


def downsample():
	# Read image
	img = cv2.imread('dog_color.jpeg')

	downsampled = cv2.pyrDown(img)

	cv2.imwrite('downsampled.jpg', downsampled)

	print('Original Image Resolutiom: {0} x {0}'.format(img.shape[0], img.shape[1]))
	print('Downsampled Image Resolution: {0} x {0}'.format(downsampled.shape[0], downsampled.shape[1]))

	cv2.waitKey(0)
	cv2.destroyAllWindows()


def histogram_equalize():
	img = cv2.imread('dog_color.jpeg', 0)
	plt.subplot(211)
	plt.hist(img.ravel(),bins=256,range=[0,256], color='b',label='before equalizing')
	plt.legend()

	# creating a Histograms Equalization
	# of a image using cv2.equalizeHist()
	equ = cv2.equalizeHist(img)
		
	# show image input vs output
	plt.subplot(212)
	plt.hist(equ.ravel(),bins=256,range=[0,256],color='r', label='after equalizing')
	plt.legend()
	plt.show()

	# stacking images side-by-side
	res = np.hstack((img, equ))

	plt.imshow(res, cmap='gray',vmin=0,vmax=255)
	plt.show()


def binary_img():
	im_gray = cv2.imread('dog_color.jpeg', 0)

	# Convert grayscale image to binary
	(thresh, im_bw) = cv2.threshold(im_gray, 128, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)

	print('thresh:', thresh)
	plt.imshow(np.hstack((im_gray, im_bw)), cmap='gray')
	plt.show()


def basic_filters(type = "gaussian"):
	img = cv2.imread('dog_color.jpeg')
	img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

	if type == 'avg':
		img1 = cv2.blur(img, (5,5))
		img2 = cv2.boxFilter(img, -1, (10, 10), normalize=True)
		plt.imshow(np.hstack((img1, img2)))

	elif type == 'gaussian':
		dst = cv2.GaussianBlur(img,(5,5),cv2.BORDER_DEFAULT) 
		plt.imshow(np.hstack((img, dst)))


	elif type == 'medium':
		dst = cv2.medianBlur(img,7)
		plt.imshow(np.hstack((img, dst)))

	elif type == 'bilateral':
		dst = cv2.bilateralFilter(img, 5, 10, 10)

		plt.imshow(np.hstack((img, dst)))

	plt.show()


def edge_finding_filters():
	img = cv2.imread('dog_color.jpeg',0)

	laplacian = cv2.Laplacian(img,cv2.CV_64F)
	sobelx = cv2.Sobel(img,cv2.CV_64F,1,0,ksize=5)
	sobely = cv2.Sobel(img,cv2.CV_64F,0,1,ksize=5)

	plt.subplot(2,2,1),plt.imshow(img,cmap = 'gray')
	plt.title('Original'), plt.xticks([]), plt.yticks([])

	plt.subplot(2,2,2),plt.imshow(laplacian,cmap = 'gray')
	plt.title('Laplacian'), plt.xticks([]), plt.yticks([])

	plt.subplot(2,2,3),plt.imshow(sobelx,cmap = 'gray')
	plt.title('Sobel X'), plt.xticks([]), plt.yticks([])

	plt.subplot(2,2,4),plt.imshow(sobely,cmap = 'gray')
	plt.title('Sobel Y'), plt.xticks([]), plt.yticks([])

	plt.show()


def dilation_erosion():
	img = cv2.imread('forest.jpeg')
	img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
	kernel = np.ones((5,5), np.uint8)
	img_erosion = cv2.erode(img, kernel, iterations=1)  
	img_dilation = cv2.dilate(img, kernel, iterations=1)
	plt.subplot(221)
	plt.imshow(img_erosion)
	plt.subplot(222)
	plt.imshow(img_dilation)
	plt.subplot(223)
	plt.imshow(img_erosion)
	plt.show()


if __name__ == '__main__':
	gamma_correction()