#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {


  cv::Mat src = cv::imread(argv[1]);
  cv::Mat gray;

  cv::cvtColor(src, gray, CV_BGR2GRAY);

  for(int y=0; y < gray.rows; y++) {
    for(int x=0; x < gray.cols; x++) {
        int a = gray.at<uchar>(y,x);
	gray.at<uchar>(y,x) = a*a;
    }
  }

  cv::imshow("input", src);
  cv::imshow("output", gray);
  cv::waitKey(0);

  return 0;
}
