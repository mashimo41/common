#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
 
using namespace cv;
 
int
main(int argc, char **argv)
{
  //Convert RGB load image
  const char *imagename = argc > 1 ? argv[1] : "Lena.JPG";
  Mat src_img = imread(imagename);
  if(!src_img.data)
    return -1;
  Mat hsv_img;
  cvtColor(src_img, hsv_img, CV_BGR2HSV);

  //Seperate HSV to 3 channels
  Mat channels[3];
  split(hsv_img, channels);

  for()

  show source and destination images 
  namedWindow("src", CV_WINDOW_NORMAL);
  imshow("src", src_img);
  namedWindow("hsv", CV_WINDOW_NORMAL);
  imshow("hsv", hsv_img);
  namedWindow("hue", CV_WINDOW_NORMAL);
  imshow("hue", channels[0]);
  namedWindow("saturation", CV_WINDOW_NORMAL);
  imshow("saturation", channels[1]);
  namedWindow("value", CV_WINDOW_NORMAL);
  imshow("value", channels[2]);

  waitKey(0);
 
  return 0;
}
