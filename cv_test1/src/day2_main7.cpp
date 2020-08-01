#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String pic_dir {"/home/tad/Picture/"};
String cascade_dir{"/usr/share/opencv4/haarcascades/"};
String file_face_xml {cascade_dir + "haarcascade_frontalface_alt.xml"};
String file_face_xml_default {cascade_dir+"haarcascade_frontalface_default.xml"};
String face_file_11 {pic_dir + "dog1.jpeg"};

int mx_value = 255;
int k_mx_value = 64;

int value_l_h=0,value_l_s=0,value_l_v=0,value_h_h=mx_value,value_h_s=mx_value,value_h_v=mx_value;
int value_k_w,value_k_h;
int value_o_w,value_o_h;

#define def_call_back(arg) void on_bar_##arg (int v,void*){value_##arg = v;}

def_call_back(o_h)
def_call_back(o_w)
def_call_back(k_w)
def_call_back(k_h)
def_call_back(l_h)
def_call_back(l_s)
def_call_back(l_v)
def_call_back(h_h)
def_call_back(h_s)
def_call_back(h_v)

int main(int argc, char const *argv[])
{
    String bg_file {pic_dir + "timg12.jpeg"};
    String ctr_wnd {"control_wnd"};
    namedWindow(ctr_wnd);

    String l_h_bar {"lower h bar"};
    createTrackbar(l_h_bar,ctr_wnd,&value_l_h,mx_value,on_bar_l_h);
    String l_s_bar {"lower s bar"};
    createTrackbar(l_s_bar,ctr_wnd,&value_l_s,mx_value,on_bar_l_s);
    String l_v_bar {"lower v bar"};
    createTrackbar(l_v_bar,ctr_wnd,&value_l_v,mx_value,on_bar_l_v);
    String h_h_bar {"hight h bar"};
    createTrackbar(h_h_bar,ctr_wnd,&value_h_h,mx_value,on_bar_h_h);
    String h_s_bar {"hight s bar"};
    createTrackbar(h_s_bar,ctr_wnd,&value_h_s,mx_value,on_bar_h_s);
    String h_v_bar {"hight v bar"};
    createTrackbar(h_v_bar,ctr_wnd,&value_h_v,mx_value,on_bar_h_v);
    String k_w_bar {"kernel width "};
    createTrackbar(k_w_bar,ctr_wnd,&value_k_w,k_mx_value,on_bar_k_w);
    String k_h_bar {"kernel height"};
    createTrackbar(k_h_bar,ctr_wnd,&value_k_h,k_mx_value,on_bar_k_h);
    String o_w_bar {"o kernel width"};
    createTrackbar(o_w_bar,ctr_wnd,&value_o_w,k_mx_value,on_bar_o_w);
    String o_h_bar {"o kernel height"};
    createTrackbar(o_h_bar,ctr_wnd,&value_o_h,k_mx_value,on_bar_o_h);

    bool is_closed = false;


    Mat src = imread(face_file_11);
    Mat bg_ = imread(bg_file);
    Mat bg;
    resize(bg_,bg,src.size());

    String main_wnd {"main_wnd"};

    String dst_wnd_1 {"dst_wnd_1"};
    String dst_wnd_2 {"dst_wnd_2"};
    String dst_wnd_3 {"dst_wnd_3"};
    String dst_wnd_4 {"dst_wnd_4"};
    String fin_wnd {"result_wnd"};

    while(!is_closed){
        imshow(main_wnd,src);

        Mat dst;
        Scalar low {value_l_h,value_l_s,value_l_v};
        Scalar hig {value_h_h,value_h_s,value_h_v};

        Mat gray;
        cvtColor(src,gray,COLOR_BGR2HSV);

        inRange(gray,low,hig,dst);

        imshow(dst_wnd_1,dst);

        Mat dst1;
        Mat kernel(value_k_h,value_k_w, CV_8U, Scalar(1));
        morphologyEx(dst,dst1,MORPH_CLOSE,kernel);
        Mat dst4;
        Mat oKer(value_o_h,value_o_w,CV_8U,Scalar(1));
        morphologyEx(dst1,dst4,MORPH_OPEN,oKer);
        imshow(dst_wnd_2,dst1);

        Mat fg = src.clone();
        fg.setTo(0,dst4);
        imshow(dst_wnd_3,fg);

        Mat bbg = bg.clone();
        Mat dst2 = 255 - dst4;
        bbg.setTo(0,dst2);
        imshow(dst_wnd_4,bbg);

        Mat fin;
        addWeighted(fg,1.0,bbg,1.0,0.0,fin);
        imshow(fin_wnd,fin);

        if(waitKey(150)>=0){
            is_closed = true;
        }
    }
    
    return 0;
}
