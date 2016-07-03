#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>


#define OPENCV_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define OPENCV_VERSION_CODE OPENCV_VERSION(CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION)

int
main(int argc, char *argv[])
{
  cv::Mat img = cv::imread("../../image/lenna.png", 1);
  if(img.empty()) return -1; 

  cv::Mat gray_img;
  cv::cvtColor(img, gray_img, CV_BGR2GRAY);
  cv::normalize(gray_img, gray_img, 0, 255, cv::NORM_MINMAX);

  std::vector<cv::KeyPoint> keypoints;
  std::vector<cv::KeyPoint>::iterator itk;
  cv::Mat descriptors;

  // threshold=0.05, edgeThreshold=10.0
  cv::SiftFeatureDetector detector(0.05,10.0);
    detector.detect(gray_img, keypoints);
  // SIFT に基づくディスクリプタ抽出器
  cv::SiftDescriptorExtractor extractor;
  cv::Scalar color(100,255,100);
  extractor.compute(gray_img, keypoints, descriptors);

  // 128次元の特徴量 x keypoint数
  for(int i=0; i<descriptors.rows; ++i) {
    cv::Mat d(descriptors, cv::Rect(0,i,descriptors.cols,1));
    std::cout << i << ": " << d << std::endl;
  }
}
