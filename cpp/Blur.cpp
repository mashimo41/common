#include <iostream>
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[]) {

  std::cout << "Usage: ./Blur.exe [filename] [option]" << std::endl;
  std::cout << "Option: Save blured image(c:Blur g:Gausian m:Median b:Bilateral )" << std::endl;
  
  const char *imagename = argc > 1 ? argv[1] : "Lena.JPG";
  cv::Mat src_img = cv::imread(imagename);
  
  if(!src_img.data) return -1; 
  
  const char ch = argc > 2 ? (argv[2])[0] : 'n';
  int flag=-1;
  switch(ch){
    
  case 'c':
    flag = 1;
    break;
      
  case 'g':
    flag = 2;
    break;
    
  case 'm':
    flag = 3;
    break;
    
  case 'b':
    flag = 4;
    break;

  }
  
  cv::Mat dst_img;
  // 入力画像，出力画像，カーネルサイズ

  //blur
  cv::blur(src_img, dst_img, cv::Size(11, 11));
  cv::namedWindow("blur image", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  cv::imshow("blur image", dst_img);
  if(flag==1) cv::imwrite("blur_image.jpg", dst_img);

  //GaussianBlur
  cv::GaussianBlur(src_img, dst_img, cv::Size(11, 11), 10, 10);
  cv::namedWindow("GaussianBlur image", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  cv::imshow("GaussianBlur image", dst_img);
  if(flag==2) cv::imwrite("blur_image.jpg", dst_img);

  //medianBlur
  cv::medianBlur(src_img, dst_img, 11);
  cv::namedWindow("medianBlur image", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  cv::imshow("medianBlur image", dst_img);
  if(flag==3) cv::imwrite("blur_image.jpg", dst_img);

  //bilateralFilter image
  cv::bilateralFilter(src_img, dst_img, -1, 50, 20);
  cv::namedWindow("bilateralFilter image", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  cv::imshow("bilateralFilter image", dst_img);
  if(flag==4) cv::imwrite("blur_image.jpg", dst_img);

  cv::waitKey(0);
		  
		  return 0;
}
