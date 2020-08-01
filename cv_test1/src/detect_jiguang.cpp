#include "opencv2/opencv.hpp"
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
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

  namedWindow(_wnd_(2));
  int i = 0;
  int bars[] = {0, 0, 0, 255, 255, 255};
  for (int &value : bars) {
    createTrackbar("bar --" + to_string(i++), _wnd_(2), &value, 255);
  }

  auto handle_it_1 = [&](Mat &src, Mat &res, Mat &draw) mutable {
    auto w = src.size().width;
    auto h = src.size().height;
    Mat mask = Mat::zeros(src.size(), CV_8UC1);
    Rect _rect{cvRound(w * (166.f / 631.f)), cvRound(h * (141.f / 478.f)),
               cvRound(w * ((335 - 166) / 631.f)),
               cvRound(h * ((380 - 141) / 478.f))};
		mask(_rect).setTo(Scalar::all(255));

    // inRange(src, Vec3b{uint8_t(bars[0]), uint8_t(bars[1]), uint8_t(bars[2])},
    // Vec3b{uint8_t(bars[3]), uint8_t(bars[4]), uint8_t(bars[5])}, res);
		 Mat temp;
		 src.copyTo(temp, mask);
		 cvtColor(temp, temp, COLOR_BGR2GRAY);
		 res = temp;
  };

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

    resize(frame, frame, {}, _resize, _resize);

    Mat to_draw = frame.clone();
    Mat res1;
    handle_it_1(frame, res1, to_draw);
    imshow(_wnd_(2), res1);
    imshow(_wnd_(1), frame);
  }

  return 0;
}

void handleIt(Mat &src) {}
