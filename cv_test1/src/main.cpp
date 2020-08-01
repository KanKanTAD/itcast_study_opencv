#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/core/version.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {

	cout<<CV_VERSION<<";"<<CV_VERSION_REVISION<<";"<<CV_VERSION_MAJOR<<"."<<CV_VERSION_MINOR<<"."<<CV_VERSION_STATUS<<endl;
  return 0;
}
