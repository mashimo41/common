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

  //Seperate HSV to 3 channels
  Mat channels[3];
  split(src_img, channels);

  // show source and destination images 
  namedWindow("src", CV_WINDOW_NORMAL);
  imshow("src", src_img);
  namedWindow("red", CV_WINDOW_NORMAL);
  imshow("red", channels[2]);
  namedWindow("blue", CV_WINDOW_NORMAL);
  imshow("blue", channels[1]);
  namedWindow("green", CV_WINDOW_NORMAL);
  imshow("green", channels[0]);

  waitKey(0);
 
  return 0;
}
