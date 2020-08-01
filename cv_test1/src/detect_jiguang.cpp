#include "opencv2/opencv.hpp"
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

using namespace std;
using namespace cv;

RNG rng(std::time(0));
#define RNG_COLOR()                                                            \
  Scalar {                                                                     \
    rng.uniform(0.0, 255.0), rng.uniform(0.0, 255.0), rng.uniform(0.0, 255.0)  \
  }

String _wnd_(int n) { return "window --" + to_string(n); }

void handleIt(Mat &);

int main(int argc, char **argv) {
  namedWindow(_wnd_(1));

  cv::CommandLineParser parser{argc, argv,
                               "{@input|0|}{resize|1.0|}{time_ms|10|}"};
  float _resize = parser.get<float>("resize");
  int _time_ms = parser.get<int>("time_ms");
  VideoCapture cap;

  String __in = parser.get<String>("@input");
  if ("0" == __in) {
    cap.open(0);
  } else {
    cap.open(__in);
  }

  bool is_continue = true;
  while (is_continue) {
    std::unique_ptr<bool, std::function<void(bool *)>> __0x00001{
        &is_continue, [&](bool *a) mutable {
          if ('\x1b' == waitKey(_time_ms)) {
            *a = false;
            if (cap.isOpened())
              cap.release();
          }
        }};

    Mat frame;
    cap >> frame;
    if (frame.empty()) {
      cap.open(__in);
      continue;
    }

    Mat _to_show;
    resize(frame, _to_show, {}, _resize, _resize);
    imshow(_wnd_(1), _to_show);
  }

  return 0;
}

void handleIt(Mat &src) {}
