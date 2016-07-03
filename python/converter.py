import numpy as np
import cv2
import sys

def cvt_gray2hsv(src):

    const = 120.
    src_gray = cv2.cvtColor(src,cv2.COLOR_BGR2GRAY)
    dst = np.zeros(src.shape, dtype=np.uint8)

    mx = np.max(src_gray)*const/256
    mn = np.min(src_gray)*const/256
    rate = const/(mx-mn)

    dst_hsv = cv2.cvtColor(dst, cv2.COLOR_BGR2HSV)
    for i in range (src.shape[0]):
        for j in range (src.shape[1]):
            dst_hsv[i,j][0] = const-(((float)(src_gray[i,j]*const/256))-mn)*rate
            dst_hsv[i,j][1] = 220
            dst_hsv[i,j][2] = 220

    dst_hsv_rgb = cv2.cvtColor(dst_hsv, cv2.COLOR_HSV2BGR)
    return(dst_hsv_rgb)

img = cv2.imread(sys.argv[1])
# img = cv2.imread("lena.jpg")
dst = cvt_gray2hsv(img)
cv2.imshow('img', img)
cv2.imshow('dst', dst)
cv2.waitKey(0)
