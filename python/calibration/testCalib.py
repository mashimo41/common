import numpy as np
import cv2
import glob

# termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
# Arrays to store object points and image points from all the images.

imgpoints = [] # 2d points in image plane.
images = glob.glob('./calib_example2/*.tif')

for fname in images:

    img = cv2.imread(fname)
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    ret = False
    # Find the chess board c  orners
    cv2.imshow('img',img)
    ret, corners = cv2.findChessboardCorners(gray, (13,12))
    # # If found, add object points, image points (after refining them)
    if ret == True:
        cv2.cornerSubPix(gray, corners, (11,11), (-1,-1), criteria)
        imgpoints.append(corners)
        # Draw and display the corners 
        cv2.drawChessboardCorners(img, (13,12), corners, ret)
        cv2.imshow('img',img)
        cv2.waitKey(0)
    if ret == False:
        print "miss"
        
cv2.waitKey(0)
for i in range (1,5):
    cv2.waitKey(1)
    cv2.destroyAllWindows()
    cv2.waitKey(1)
imgpoints = np.array(imgpoints,'float32')
# print len(corners), len(pattern_points)
