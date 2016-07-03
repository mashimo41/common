#include "Labeling.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
  
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
  // 大津の手法を利用するので閾値適当
  // CV_THRESH_BINARY_INVは必須。
  cv::Mat binimg;
  cv::threshold(grayimg, binimg, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
 
  // Labelingの結果を受け取る
  cv::Mat label(image.size(), CV_16SC1);
 
  // ラベリングを実施 ２値化した画像に対して実行する。
  LabelingBS labeling;
  labeling.Exec(binimg.data, (short *)label.data, image.cols, image.rows, false, 0);
  
  // ラベリング結果を出力する、真っ白な状態で初期化
  cv::Mat outimg(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
  
  // ラベルされた領域をひとつずつ描画
  for( int i = 0; i < labeling.GetNumOfRegions(); i++)
    {
      // ラベリング結果でイロイロする。
      // ラベリング結果の領域を抽出する。
      cv::Mat labelarea;
      cv::compare(label, i + 1, labelarea, CV_CMP_EQ);
      // 抽出した領域にランダムな色を設定して出力画像に追加。
      cv::Mat color(image.size(), CV_8UC3, randomColor());
      color.copyTo(outimg, labelarea);
    }
  // 入力画像とラベリング結果の画像を画面表示
  imshow("image", image);
  imshow("label", outimg);
  cv::waitKey();
  cv::hconcat(image, outimg, outimg);
  // ラベルされた出力画像を保存
  cv::imwrite("labeled.png", outimg);
  
  return 0;
}
