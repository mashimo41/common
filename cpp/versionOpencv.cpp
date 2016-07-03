#include <iostream>
#include <opencv2/core/core.hpp>

#define OPENCV_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define OPENCV_VERSION_CODE OPENCV_VERSION(CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION)

int
main(int argc, char *argv[])
{
  std::cout << "version: " << CV_VERSION << std::endl;
  std::cout << "  major: " << CV_MAJOR_VERSION << std::endl;
  std::cout << "  minor: " << CV_MINOR_VERSION << std::endl;
  std::cout << "  subminor: " << CV_SUBMINOR_VERSION << std::endl;
  std::cout << "OpenCV >= 2.0.0: " << (OPENCV_VERSION_CODE>=OPENCV_VERSION(2,0,0)?"true":"false") << std::endl;
}
