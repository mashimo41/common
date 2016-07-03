#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char *argv[]) {
  // グレースケール画像として読み込む
  cv::Mat src = cv::imread(argv[1], 0);
  if(src.empty()) return -1; 

  //cv::Mat src_img;
  //cv::bilateralFilter(src, src_img, -1, 30, 20);  
  // Sobel
  cv::Mat tmp_img;
  cv::Mat sobel_img;
  cv::Sobel(src_img, tmp_img, CV_32F, 1, 1);
  cv::convertScaleAbs(tmp_img, sobel_img, 1, 0);

  // Laplacian
  cv::Mat laplacian_img;
  cv::Laplacian(src_img, tmp_img, CV_32F, 3);
  cv::convertScaleAbs(tmp_img, laplacian_img, 1, 0);
  
  // Canny
  cv::Mat canny_img;
  cv::Canny(src_img, canny_img, 50, 200);

  cv::namedWindow("Original(Grayscale)", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  cv::namedWindow("Sobel", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  cv::namedWindow("Laplacian", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  cv::namedWindow("Canny", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  cv::imshow("Original(Grayscale)", src_img);
  cv::imshow("Sobel", sobel_img);
  cv::imshow("Laplacian", laplacian_img);
  cv::imshow("Canny", canny_img);
  cv::waitKey(0);
}
