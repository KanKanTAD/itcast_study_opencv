#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <random>


using namespace std;
using namespace cv;

String pic_dir {"/home/tad/Picture/"};

void mao_po_li(Mat& res,const Rect& roi,const Size& sz){
	Mat src {res.clone()};	
	auto && size_ = src.size();
	auto height = size_.height;
	auto width = size_.width;

	auto height_top = std::min(height,roi.y + roi.height);
	auto width_top = std::min(width,roi.x + roi.width);

	srand(time(0));
	for(int r=roi.y;r < height_top;r+=sz.height){
		for(int c=roi.x;c < width_top;c+=sz.width){

			auto w = c+sz.width < width_top ? sz.width : width_top - c;
			auto h = r+sz.height < height_top ? sz.height : height_top - r;

			Rect rect_ {c,r,w,h};
			
			cv::randShuffle(res(rect_));
			//randn(res(rect_), Scalar::all(0), Scalar::all(255));
		}
	}

}

#define def_call_and_value(arg) int value_##arg=0; \
																void callback_##arg(int a,void*){ \
																	value_##arg = a; \
																}

def_call_and_value(rect_x)
def_call_and_value(rect_y)
def_call_and_value(rect_w)
def_call_and_value(rect_h)
//def_call_and_value(sz_w)
//def_call_and_value(sz_h)
int value_sz_w = 1;
void callback_sz_w(int a,void*){
	value_sz_w = 1 + a;
}
int value_sz_h = 1;
void callback_sz_h(int a,void*){
	value_sz_h = 1 + a;
}

#define create_bar_to_wnd(bar_name,wnd_name,count) String name_bar_##bar_name {#bar_name}; \
	cv::createTrackbar(name_bar_##bar_name,wnd_name,&value_##bar_name,count,callback_##bar_name);

int main(int argc,char** argv) {

	String ctl_wnd_name {"ctrl_wnd"};
	namedWindow(ctl_wnd_name);


	String file_path {pic_dir + "face11.jpeg"};
	auto frame = imread(file_path);

	create_bar_to_wnd(rect_x,ctl_wnd_name,frame.size().width);
	create_bar_to_wnd(rect_y,ctl_wnd_name,frame.size().height);
	create_bar_to_wnd(rect_h,ctl_wnd_name,frame.size().height);
	create_bar_to_wnd(rect_w,ctl_wnd_name,frame.size().width);
	create_bar_to_wnd(sz_w,ctl_wnd_name,64);
	create_bar_to_wnd(sz_h,ctl_wnd_name,64);

	String wnd_name {"main_wnd"};
	namedWindow(wnd_name);

	String burl_name1 {"mao po li wnd"};
	namedWindow(burl_name1);

	bool is_stop = false;

	while(!is_stop){

		imshow(wnd_name,frame);
		Mat res {frame.clone()};
		Rect roi {value_rect_x,value_rect_y,value_rect_w,value_rect_h};
		Size sz {value_sz_w,value_sz_h};
		mao_po_li(res, roi, sz);

		imshow(burl_name1,res);

		if(waitKey(150) >= 0){
			is_stop = true;
		}
	}


	return 0;
}
