#include "Labeling.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>  

// 適当な色を出す用
cv::RNG rnd(1192);
cv::Scalar randomColor()
{
  return cv::Scalar(rnd.next() & 0xFF, rnd.next() & 0xFF, rnd.next() & 0xFF);
}
 
int main(int argc, char* argv[])
{
  // 入力画像を読み込み
  cv::Mat image = cv::imread("IMG_2331_resize.jpg");
  
  // グレイスケール化(3チャンネル→1チャンネル化)
  cv::Mat grayimg;
  cv::cvtColor(image, grayimg, CV_BGR2GRAY);
 
  // 二値化
  cv::Mat binimg;
  cv::threshold(grayimg, binimg, 50, 255, CV_THRESH_BINARY);
 
  // Labelingの結果を受け取る
  cv::Mat label(image.size(), CV_16SC1);
 
  // ラベリングを実施 ２値化した画像に対して実行する。
  LabelingBS labeling;
  labeling.Exec(binimg.data, (short *)label.data, image.cols, image.rows, false, 1000);


  // (4)detect and draw strong corners on the image using Harris detector 
  std::vector<cv::Point2f> corners;
  std::vector<cv::Point2f>::iterator it_corner;
  cv::Mat harris_img = image.clone();
  cv::goodFeaturesToTrack(grayimg, corners, 80, 0.01, 5, cv::Mat(), 3, true);
  
  // ラベリング結果を出力する、真っ白な状態で初期化
  cv::Mat outimg(image.size(), CV_8UC3, cv::Scalar(0, 0, 0));
  cv::imwrite("sample.jpg", outimg);  
  // ラベルされた領域をひとつずつ描画
  for( int i = 0; i < labeling.GetNumOfRegions(); i++) {
    // ラベリング結果の領域を抽出する。
    cv::Mat labelarea;
    cv::compare(label, i + 1, labelarea, CV_CMP_EQ);
    // 抽出した領域にランダムな色を設定して出力画像に追加。
    //cv::Mat color(image.size(), CV_8UC3, randomColor());
    int cornersEachBlur[2][20]={0};
    int j=0;
    for(it_corner = corners.begin(); it_corner!=corners.end(); ++it_corner) {
      cv::circle(harris_img, cv::Point(it_corner->x, it_corner->y), 8, cv::Scalar(0+i*40,i*50,255-i*40));
      if(labelarea.at<uchar>(it_corner->y, it_corner->x)>0) {
	cornersEachBlur[0][j]=it_corner->x;
	cornersEachBlur[1][j]=it_corner->y;
	j++;
      }
      if(j==10) break;
    }
    double dx = (double)cornersEachBlur[0][1] - (double)cornersEachBlur[0][0];
    double dy = (double)cornersEachBlur[1][1] - (double)cornersEachBlur[1][0];
    double v = sqrt( dx*dx + dy*dy );
    std::cout << v << std::endl;
    //color.copyTo(outimg, labelarea);
    harris_img.copyTo(outimg, labelarea);
  }
  // 入力画像とラベリング結果の画像を画面表示
  imshow("image", image);
  imshow("label", outimg);
  imshow("harris", harris_img);
  cv::waitKey();
  cv::hconcat(image, outimg, outimg);
  // ラベルされた出力画像を保存
  cv::imwrite("labeled.png", harris_img);
  
  return 0;
}
