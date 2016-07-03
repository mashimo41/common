#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {

  Mat m1 = (Mat_<float>(3,3) << 1, 2, 3, 0, 0, 0, 1, 0, 0);
  Mat m2 = (Mat_<float>(3,1) << 1, 2, 1);
  Mat m3;
  m3 = m1*m2;
  cout << m1 << endl;
  cout << m2 << endl;
  cout << m3 << endl;










  return 0;

}
