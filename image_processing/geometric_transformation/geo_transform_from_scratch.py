import cv2
import numpy as np
import matplotlib.pyplot as plt

def get_grid(x, y, homogenous=False):
    coords = np.indices((x, y)).reshape(2, -1)
    return np.vstack((coords, np.ones(coords.shape[1]))).astype(np.int) if homogenous else coords


def grid_plotter(points, labels):
    markers = ['o', 'x', 's', '^', 'p', 'v']
    fig, ax = plt.subplots(figsize=(8,6))
    for i, p in enumerate(points):
        x, y = p[0], p[1]
        ax.scatter(x, y, label=labels[i], marker=markers[i], alpha=0.8, s=100)
    ax.legend(loc='lower right')
    ax.set_xlim(-5, 5)
    ax.set_ylim(-5, 5)

    ax.grid(True)
    plt.show()


def show_image(image):
    fig, ax = plt.subplots(figsize=(8,6))
    ax.imshow(image)
    plt.show()


def get_rotation(angle):
    angle = np.radians(angle)
    return np.array([
        [np.cos(angle), -np.sin(angle), 0],
        [np.sin(angle),  np.cos(angle), 0],
        [0, 0, 1]
    ])


def get_translation(tx, ty):
    return np.array([
        [1, 0, tx],
        [0, 1, ty],
        [0, 0, 1]
    ])


def get_scale(s):
    return np.array([
        [s, 0, 0],
        [0, s, 0],
        [0, 0, 1]
    ])


R1 = get_rotation(135)
T1 = get_translation(-2, 2)
S1 = get_scale(2)


# Get sample coordinates
coords = get_grid(2, 2, homogenous=True)
print(coords)

# Apply transformation
coords_rot = R1 @ coords
coords_trans = T1 @ coords
coords_scale = S1 @ coords
coords_composite1 = R1 @ T1 @ coords
coords_composite2 = T1 @ R1 @ coords

# grid_plotter([coords, coords_rot, coords_trans, coords_scale, coords_composite1, coords_composite2],
#              labels=['original', 'rotate135', 'translate(-2, 2)', 'scale(2)', 'translate(-2, 2), rotate(135)', 'rotate(135), translate(-2, 2)'])


def translation():
    # Read an image
    img = cv2.imread('D:\\Workspace\\intern\\vccorp\\image_processing\\point_operators\\dog_color.jpeg')
    rows,cols,_ = img.shape

    # Create the transformation matrix
    M = np.float32([[1,0,100],[0,1,50]])
    
    # get the coordinates in the form of (0,0),(0,1)...
    # the shape is (2, rows*cols)
    orig_coord = np.indices((cols, rows)).reshape(2,-1)

    # stack the rows of 1 to form [x,y,1]
    orig_coord_f = np.vstack((orig_coord, np.ones(rows*cols)))
    transform_coord = np.dot(M, orig_coord_f)

    # Change into int type
    transform_coord = transform_coord.astype(np.int)

    # Keep only the coordinates that fall within the image boundary.
    indices = np.all((transform_coord[1]<rows, transform_coord[0]<cols, transform_coord[1]>=0, transform_coord[0]>=0), axis=0)

    # Create a zeros image and project the points
    img1 = np.zeros_like(img)
    img1[transform_coord[1][indices], transform_coord[0][indices]] = img[orig_coord[1][indices], orig_coord[0][indices]]

    # Display the image
    out = cv2.hconcat([img,img1])
    cv2.imshow('a2',out)
    cv2.waitKey(0)


def rotation():

# Read an image
    img = cv2.imread('D:\\Workspace\\intern\\vccorp\\image_processing\\point_operators\\dog_color.jpeg')
    rows,cols,_ = img.shape

    # Create the transformation matrix
    angle = np.radians(90)
    x0, y0 = ((cols-1)/2.0,(rows-1)/2.0)
    M = np.array([[np.cos(angle), -np.sin(angle), x0*(1-np.cos(angle))+ y0*np.sin(angle)],
                [np.sin(angle), np.cos(angle), y0*(1-np.cos(angle))- x0*np.sin(angle)]])
    # get the coordinates in the form of (0,0),(0,1)...
    # the shape is (2, rows*cols)
    orig_coord = np.indices((cols, rows)).reshape(2,-1)
    # stack the rows of 1 to form [x,y,1]
    orig_coord_f = np.vstack((orig_coord, np.ones(rows*cols)))
    transform_coord = np.dot(M, orig_coord_f)
    # Change into int type
    transform_coord = transform_coord.astype(np.int)
    # Keep only the coordinates that fall within the image boundary.
    indices = np.all((transform_coord[1]<rows, transform_coord[0]<cols, transform_coord[1]>=0, transform_coord[0]>=0), axis=0)
    # Create a zeros image and project the points
    img1 = np.zeros_like(img)
    img1[transform_coord[1][indices], transform_coord[0][indices]] = img[orig_coord[1][indices], orig_coord[0][indices]]
    # Display the image
    out = cv2.hconcat([img,img1])
    cv2.imshow('a2',out)
    cv2.waitKey(0)


rotation()