#!/usr/bin/env python
# -*- coding: utf-8 -*-
""" 宿題: 画像処理の基本

使い方:
    $ python assignment.py

Written by Kyohei Otsu <kyon@ac.jaxa.jp> on 2015-05-07
"""

import cv2
import numpy as np

def extract_red(img):
    '''
        TODO: 赤い領域だけ検出し、1チャネル画像として返す
    '''
    out = np.zeros(img.shape, dtype=np.uint8)

    # Implement main process here

    return out


def replace_green_by_blue(img):
    '''
        TODO: 緑の領域を青色に変える 
    '''
    out = np.zeros(img.shape, dtype=np.uint8)

    # Implement main process here

    return out


def drink_rose_yuko(img):
    '''
        TODO: 竹内結子の飲むビールをお洒落にロゼに変える
    '''
    out = np.zeros(img.shape, dtype=np.uint8)

    # Implement main process here

    return out


################################################################################
# メイン
################################################################################
if __name__ == '__main__':

    # 課題1
    img = cv2.imread('q1_circle.png')
    out = extract_red(img)

    # 課題2
    #img = cv2.imread('q1_circle.png')
    #out = replace_green_by_blue(img)

    # 発展課題
    #img = cv2.imread('q2_yuko.jpg')
    #out = drink_rose_yuko(img)

    cv2.imshow('Input',  img)
    cv2.imshow('Output', out)
    cv2.waitKey(-1)

