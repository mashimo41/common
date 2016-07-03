#coding:utf-8
import numpy as np
import cv2

def cvt_gray2hsv(src):
#画像の読み込み

#または
    const=181/256

    #src=cv2.imread('ringo.jpg',1)
    src_gray=cv2.cvtColor(src,cv2.COLOR_BGR2GRAY)
    dst = np.zeros(src.shape, dtype=np.uint8)
    dst_hsv=cv2.cvtColor(dst,cv2.COLOR_BGR2HSV)
    for i in range (src.shape[0]):
        for j in range (src.shape[1]):
            dst_hsv[i,j][0]=src_gray[i,j]*const
            dst_hsv[i,j][1]=200
            dst_hsv[i,j][2]=200

    dst_hsv_rgb=cv2.cvtColor(dst_hsv,cv2.COLOR_HSV2BGR)
    return(dst_hsv_rgb)

    
    # print(dst_hsv)
    # print(dst_hsv.shape)
    # print(dst_hsv_rgb)
    # print(dst.shape)
    
    # cv2.imshow('src',src)
    # cv2.imshow('src_gray',src_gray)
    # cv2.imshow('dst_hsv',dst_hsv)
    # cv2.imshow('dst_hsv_rgb',dst_hsv_rgb)

img = cv2.imread("lena.bmp")
dst = cvt_gray2hsv(img)
cv2.imshow('img', img)
cv2.imshow('dst', dst)

    # ##cv2.imshow('image', img)
cv2.waitKey(0)
    # cv2.destroyAllWindows()
