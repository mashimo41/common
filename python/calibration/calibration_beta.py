#coding:utf-8
#!/usr/bin/env python

'''
input: chessboard images(more than 10)
output: 1.corner drawed distort images
        2.undistorted images

other parameters:
  img_names = input images
  debug_dir = output directory
  square_size = scale factor between image plane and 3d real world frame
  pattern_size = the numbers of corners(vertical & horizontal)

入力画像と出力ディレクトリを指定すると，コーナー描画画像とひずみ補正
画像が出力される．コーナー描画画像をみて，コーナーが検出できる画像と
できない画像を選別する．また，縦と横のコーナー数を指定することが必須

※　コーナー数の数え方に注意
2つの黒色矩形の接点をコーナー(interior corner)と定義している．よって，
10x10のチェスボードの場合は指定すべきコーナー数は9x9となる．
'''

from __future__ import print_function #for using end ='' in print "xxx"
import numpy as np
import cv2
import glob
from common import splitfn # local modules for useing splitfn()

if __name__ == '__main__':

    ####################################################
    # パラメータ設定
    ####################################################
    # img_names: チェスボード画像(10枚以上)
    # debug_dir: 出力ディレクトリ
    # square_size: チェス格子サイズ(普通は1)
    # pattern_size: 格子点数(横，縦)

    # 調布実験
    img_names = glob.glob('./0609Chofu/*.png')
    debug_dir = './output_0609Chofu/'
    square_size = 1.0
    pattern_size = (10, 7) #chofu

    # calib_example
    # img_names = glob.glob('./calib_example/*.jpg')
    # debug_dir = './output_ex/'
    # square_size = 1.0
    # pattern_size = (6, 9) #calib_example

    # calib_example2
    # img_names = glob.glob('./calib_example2/*.tif')
    # debug_dir = './output_ex2/'
    # square_size = 1.0
    # pattern_size = (13, 12) #calib_example2


    ####################################################
    # 変数宣言，初期化
    ####################################################

    pattern_points = np.zeros((np.prod(pattern_size), 3), np.float32)
    pattern_points[:, :2] = np.indices(pattern_size).T.reshape(-1, 2)
    pattern_points *= square_size

    obj_points = [] # 3d points in real world space
    img_points = [] # 2d points in image plane

    h, w = 0, 0
    img_names_undistort = []

    ####################################################
    # コーナー検出・座標取得
    ####################################################
    for fn in img_names: #process all image files

        # 現在何番目の画像が処理されているか？
        # 画像が読み込めない場合は飛ばす
        print("processing %s... " % fn, end='')
        img = cv2.imread(fn, 0) #Gray scale image
        if img is None:
            print("Failed to load", fn)
            continue

        # コーナー検出,コーナー座標取得
        # 戻り値は検出の有無（True,False），コーナー座標
        h, w = img.shape[:2]
        found, corners = cv2.findChessboardCorners(img, pattern_size)
        
        # print(corners.shape[0], corners.shape[1], corners.size)

        # サブピクセル精度でコーナー座標取得
        if found:
            term = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_COUNT, 30, 0.1)
            cv2.cornerSubPix(img, corners, (5, 5), (-1, -1), term)

        if not found:
            print("chessboard not found")
            continue

        # 画像平面でのコーナー座標，3D空間でのコーナー座標取得
        img_points.append(corners.reshape(-1, 2))
        obj_points.append(pattern_points)

        # コーナー描画，描画画像保存
        if debug_dir:
            vis = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
            cv2.drawChessboardCorners(vis, pattern_size, corners, found)
            path, name, ext = splitfn(fn)
            outfile = debug_dir + name + '_chess.png'
            # outfile:保存ファイル名，vis:コーナー描画画像
            cv2.imwrite(outfile, vis)
            if found:
                img_names_undistort.append(outfile)
                # list of images which should be undistorted

        # コーナー座標取得が完了したかどうか
        print("ok")

    ####################################################
    # キャリブレーション
    ####################################################
    # 内部変数，外部変数，RMS計算
    rms, camera_matrix, dist_coefs, rvecs, tvecs = cv2.calibrateCamera(obj_points, img_points, (w, h))

    print("\nRMS:", rms)
    print("camera matrix:\n", camera_matrix)
    print("distortion coefficients: ", dist_coefs.ravel())

    # ひずみ補正
    print('')
    for img_found in img_names_undistort:
        img = cv2.imread(img_found)

        # ひずみ補正するためにカメラ行列・画像サイズを最適化
        h,  w = img.shape[:2]
        newcameramtx, roi = cv2.getOptimalNewCameraMatrix(camera_matrix, dist_coefs, (w, h), 1, (w, h))

        # 補正
        dst = cv2.undistort(img, camera_matrix, dist_coefs, None, newcameramtx)

        # 最適化した画像サイズで保存

        # ひずみが目立たなくなるように端を切っている模様
        x, y, w, h = roi
        dst = dst[y:y+h, x:x+w]
        outfile = img_found + '_undistorted.png'
        print('Undistorted image written to: %s' % outfile)
        cv2.imwrite(outfile, dst)

cv2.destroyAllWindows()

    ####################################################
    # オプション定義
    ####################################################
    # args, img_mask = getopt.getopt(sys.argv[1:], '', ['debug=', 'square_size='])
    # args = dict(args)

    # # デフォルト値の指定
    # args.setdefault('--debug', './output/')
    # args.setdefault('--square_size', 1.0)
    # if not img_mask:
    #     img_mask = './calib_example/left*.jpg'
    # else:
    #     img_mask = img_mask[0]

    # # オプションの読み込み
    # img_names = glob('./calib_example2/*.tif')
    # debug_dir = args.get('--debug')
    # if not os.path.isdir(debug_dir):
    #     os.mkdir(debug_dir)
    # square_size = float(args.get('--square_size'))
