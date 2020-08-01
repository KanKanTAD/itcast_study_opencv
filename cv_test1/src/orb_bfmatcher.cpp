#include "opencv2/opencv.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/shape/shape_transformer.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;

String pic_dic{"/home/tad/Picture/"};

struct __util_t {

  Mat trainImage;
  Mat queryImage;
  vector<DMatch> matches;
  vector<KeyPoint> train_pts;
  vector<KeyPoint> query_pts;
  Mat res;
};

int main(int argc, char **argv) {

  cv::CommandLineParser parser{
      argc, argv, "{@traninImage|box.png|}{@queryImage|box_in_scene.png|}"};
  parser.printMessage();

  namedWindow("result");

  __util_t ut;

  ut.trainImage = imread(pic_dic + parser.get<String>("@traninImage"));
  ut.queryImage = imread(pic_dic + parser.get<String>("@queryImage"));

  Mat image1, image2;
  cvtColor(ut.trainImage, image1, COLOR_BGR2GRAY);
  cvtColor(ut.queryImage, image2, COLOR_BGR2GRAY);

  Ptr<ORB> detector = ORB::create();

  Mat train_desc, query_desc;

  detector->detectAndCompute(image1, Mat{}, ut.train_pts, train_desc);
  detector->detectAndCompute(image2, Mat{}, ut.query_pts, query_desc);

  Ptr<BFMatcher> matcher = BFMatcher::create(NORM_HAMMING, true);
  matcher->match(train_desc, query_desc, ut.matches);

  std::sort(
      ut.matches.begin(), ut.matches.end(),
      [](DMatch &a, DMatch &b) -> bool { return a.distance < b.distance; });

  void (*runner)(int, void *) = [](int a, void *_ut) {
    static int cnt = 1;
    __util_t &data = *((__util_t *)_ut);
    int sz = std::min(int(data.matches.size()), std::max(4, a));
    drawMatches(data.trainImage, data.train_pts, data.queryImage,
                data.query_pts,
                vector<DMatch>{data.matches.begin(), data.matches.begin() + sz},
                data.res, Scalar::all(-1), Scalar::all(-1), vector<char>{},
                DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    vector<Point2f> ori_pts;
    for (int i = 0; i < sz; i++) {
      ori_pts.emplace_back(data.train_pts.at(data.matches.at(i).trainIdx).pt);
    }
    vector<Point2f> tag_pts;
    for (int i = 0; i < sz; ++i) {
      tag_pts.emplace_back(data.query_pts.at(data.matches.at(i).queryIdx).pt);
    }
    Mat homograph_ = findHomography(ori_pts, tag_pts, RANSAC, 5.0);
    cout << "cout------" << cnt++ << endl;
    cout << "homograph_" << endl;
    cout << homograph_ << endl;

    Mat perspective_ = getPerspectiveTransform(
        vector<Point2f>{ori_pts.begin(), ori_pts.begin() + 4},
        vector<Point2f>{tag_pts.begin(), tag_pts.begin() + 4});
    cout << "perspective_" << endl;
    cout << perspective_ << endl;

    Mat affine_ = getAffineTransform(
        vector<Point2f>{ori_pts.begin(), ori_pts.begin() + 3},
        vector<Point2f>{tag_pts.begin(), tag_pts.begin() + 3});
    cout << "affine_" << endl;
    cout << affine_ << endl;
  };

  int MAX_MATCHES = 4;
  createTrackbar("matchs", "result", &MAX_MATCHES, int(ut.matches.size()),
                 runner, &ut);
  runner(MAX_MATCHES, &ut);

  while ('\x1b' != waitKey(30)) {
    imshow("result", ut.res);
  }
  return 0;
}
