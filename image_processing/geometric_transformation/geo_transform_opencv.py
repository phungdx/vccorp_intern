import cv2
import numpy as np
from matplotlib import pyplot as plt

def resize():
	img = cv2.imread('D:\\Workspace\\intern\\vccorp\\image_processing\\point_operators\\forest.jpeg')

	res = cv2.resize(img,None,fx=2, fy=2, interpolation = cv2.INTER_CUBIC)
	print(img.shape)
	print(res.shape)

	#OR

	# height, width = img.shape[:2]
	# res = cv2.resize(img,(2*width, 2*height), interpolation = cv2.INTER_CUBIC)


def translation():
	img = cv2.imread('D:\\Workspace\\intern\\vccorp\\image_processing\\point_operators\\forest.jpeg',0)
	rows,cols = img.shape

	# matrix transformation
	M = np.float32([[1,0,100],[0,1,50]])
	dst = cv2.warpAffine(img, M, (cols,rows))

	cv2.imshow('img',dst)
	cv2.waitKey(0)
	cv2.destroyAllWindows()


def rotation():
	img = cv2.imread('D:\\Workspace\\intern\\vccorp\\image_processing\\point_operators\\dog_color.jpeg',0)
	rows, cols = img.shape
	center = (cols/2, rows/2)
	M = cv2.getRotationMatrix2D(center, 90, 1)
	dst = cv2.warpAffine(img,M,(cols, rows))

	cv2.imshow('img',dst)
	cv2.waitKey(0)
	cv2.destroyAllWindows()


def affine_transform():
	img = cv2.imread('D:\\Workspace\\intern\\vccorp\\image_processing\\point_operators\\dog_color.jpeg')
	img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
	rows,cols,ch = img.shape

	# create mirror image
	input_pts = np.float32([[0,0], [cols-1,0], [0,rows-1]])
	output_pts = np.float32([[cols-1,0], [0,0], [cols-1,rows-1]])

	M = cv2.getAffineTransform(input_pts,output_pts)

	dst = cv2.warpAffine(img,M,(cols,rows))

	plt.subplot(121),plt.imshow(img),plt.title('Input')
	plt.subplot(122),plt.imshow(dst),plt.title('Output')
	plt.show()


def perspective_transform():
	img = cv2.imread('D:\\Workspace\\intern\\vccorp\\image_processing\\point_operators\\dog_color.jpeg')
	img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
	rows,cols,ch = img.shape

	inputs = np.float32([[56,65],[368,52],[28,387],[389,390]])
	outputs = np.float32([[0,0],[300,0],[0,300],[300,300]])

	M = cv2.getPerspectiveTransform(inputs,outputs)

	dst = cv2.warpPerspective(img,M,(300,300))

	plt.subplot(121),plt.imshow(img),plt.title('Input')
	plt.subplot(122),plt.imshow(dst),plt.title('Output')
	plt.show()


perspective_transform()