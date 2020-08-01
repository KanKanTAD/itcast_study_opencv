#include "opencv2/opencv.hpp"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <functional>
#include <ios>
#include <iostream>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/core/core_c.h>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <set>
#include <string>
#include <vector>

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
  int bars[] = {0, 0, 0, 255, 255, 255, 3, 3, 3, 3, 3};
  for (int &value : bars) {
    createTrackbar("bar --" + to_string(i++), _wnd_(2), &value, 255);
  }
  int min_contour_area = 10;
  createTrackbar("min_contour_area", _wnd_(2), &min_contour_area, 2000);

  auto handle_it_1 = [&](Mat &src, Mat &res, Mat &draw) mutable {
    auto w = src.size().width;
    auto h = src.size().height;
    Mat mask = Mat::zeros(src.size(), CV_8UC1);
    Rect _rect{cvRound(w * (189.f / 631.f)), cvRound(h * (167.f / 478.f)),
               cvRound(w * ((300.f - 189.f) / 631.f)),
               cvRound(h * ((366.f - 167.f) / 478.f))};
    mask(_rect).setTo(Scalar::all(255));

    Mat hsv;
    cvtColor(src, hsv, COLOR_BGR2HSV);

    int channels[] = {0, 1, 2};
    Mat hist;
    bars[6] = 15;
    bars[7] = 48;
    bars[8] = 1;
    int calcSize[] = {std::max(1, bars[6]), std::max(1, bars[7]),
                      std::max(1, bars[8])};
    float hranges[] = {0, 180}, sranges[] = {0, 256}, vranges[] = {0, 256};
    const float *_ranges[] = {hranges, sranges, vranges};
    calcHist(&hsv, 1, channels, mask, hist, 3, calcSize, _ranges, true, false);
    Mat backProject;
    Mat __hsv = hsv(_rect).clone();
    calcBackProject(&__hsv, 1, channels, hist, backProject, _ranges);
    bars[9] = 5;
    bars[10] = 5;
    blur(backProject, backProject,
         {std::max(bars[9], 1), std::max(bars[10], 1)});
    bitwise_not(backProject, backProject);
    threshold(backProject, backProject, 0, 255,
              THRESH_BINARY | cv::THRESH_OTSU);
    res = Mat::zeros(src.size(), backProject.type());
    backProject.copyTo(res(_rect));

    vector<vector<Point2i>> contours;
    std::set<Point2i> set_hull;
    findContours(res, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    if (contours.empty())
      return;
    for (int i = 0; i < contours.size(); ++i) {
      if (contourArea(contours.at(i)) <= min_contour_area) {
        continue;
      }
      // drawContours(draw, contours, i, Scalar(255,255,0), -1);
      set_hull.insert(contours.at(i).begin(), contours.at(i).end());
    }
    vector<Point2i> _hull{set_hull.begin(), set_hull.end()};
    vector<Point2i> hl;

    cv::convexHull(_hull, hl);
    vector<Point2i> approx;
    double esplion = 0.02 * arcLength(hl, true);
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
    imshow(_wnd_(1), to_draw);
  }

  return 0;
}

void handleIt(Mat &src) {}
