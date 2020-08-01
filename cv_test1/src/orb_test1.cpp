#include "opencv2/core/types.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <iostream>
#include <opencv2/core/cvstd.hpp>
#include <vector>

using namespace std;
using namespace cv;
int main(int argc, char *argv[]) {
  CommandLineParser parser{argc, argv,
                           "{@input|house.jpg|}{pic_dir|/home/tad/Picture/|}"};
  parser.printMessage();

  Mat src =
      imread(parser.get<String>("pic_dir") + parser.get<String>("@input"));

  Mat res;
  cvtColor(src, res, COLOR_BGR2GRAY);
	vector<KeyPoint> keypoints;

	Ptr<ORB> orb = ORB::create();
	orb->detect(res,keypoints);

	drawKeypoints(src, keypoints, src);

	imshow("show",src);

	waitKey();

  return 0;
}
