#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>

int main(int argc, char *argv[]) {

  // 画像を読み込む
  cv::Mat bgrImage = cv::imread(argv[1]);

  // 特徴点を格納する変数
  std::vector<cv::KeyPoint> keyPoints;
  // SIFTを用いた特徴点抽出
  cv::SurfFeatureDetector surf;
  surf.detect(bgrImage, keyPoints);

  // 特徴点を描画
  cv::Mat featureImage;
  cv::drawKeypoints(bgrImage,
		    keyPoints,
		    featureImage,
		    cv::Scalar(255, 255, 255),
		    cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

  // 特徴点が描かれた画像を表示
  cv::namedWindow("Feature image", CV_WINDOW_NORMAL);
  cv::imshow("Feature image", featureImage);
  cv::waitKey(0);

  return 0;
}
