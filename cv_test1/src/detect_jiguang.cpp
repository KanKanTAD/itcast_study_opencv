#include "opencv2/opencv.hpp"
#include <ctime>
#include <iostream>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

RNG rng(std::time(0));

void handleIt(Mat &);

int main(int argc, char **argv) {

  cv::CommandLineParser parser{argc, argv,
                               "{@input|test_aubo2.png|}{resize|1.0|}"};

  while (true) {

    if ('\x1b' == waitKey(150)) {
      break;
    }
  }

  return 0;
}

void handleIt(Mat &src) {}
