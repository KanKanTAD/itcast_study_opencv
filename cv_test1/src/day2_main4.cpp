#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using std::cout;

const String pic_dir {"/home/tad/Picture/"};

const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;
Mat src1;
Mat src2;
Mat dst;
static void on_trackbar( int arg1, void* arg2)
{
   cout<<arg1<<";"<<std::endl;
   alpha = (double) alpha_slider/alpha_slider_max ;
   beta = ( 1.0 - alpha );
   addWeighted( src1, alpha, src2, beta, 0.0, dst);
   imshow( "Linear Blend", dst );
}
int main( void )
{
   src1 = imread( pic_dir + "timg23.jpeg");
   src2 = imread( pic_dir + "timg31.jpeg");
   if( src1.empty() ) { cout << "Error loading src1 \n"; return -1; }
   if( src2.empty() ) { cout << "Error loading src2 \n"; return -1; }
   alpha_slider = 0;
   namedWindow("Linear Blend", WINDOW_AUTOSIZE); // Create Window
   char TrackbarName[50];
   sprintf( TrackbarName, "Alpha x %d", alpha_slider_max );
   createTrackbar( TrackbarName, "Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar );
   on_trackbar( alpha_slider, 0 );
   waitKey(0);
   return 0;
}