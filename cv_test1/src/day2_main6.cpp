#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String pic_dir {"/home/tad/Picture/"};
String cascade_dir{"/usr/share/opencv4/haarcascades/"};
String file_face_xml {cascade_dir + "haarcascade_frontalface_alt.xml"};
String file_face_xml_default {cascade_dir+"haarcascade_frontalface_default.xml"};
String face_file_11 {pic_dir + "face11.jpeg"};

const Scalar SCALAR_RED {48,48,200};

int tickness1 = 1;
int detect_times = 1;

void draw_ellipse(Mat& frame,const Rect& rect,const Scalar& color=SCALAR_RED){
    int w = rect.width / 2;
    int h = rect.height/ 2;
    Point center {rect.x + w,rect.y + h};
    Size sz {w,h};
    ellipse(frame,center,sz,0,0,360,color, tickness1);
}

void detect_face(Mat& frame,CascadeClassifier& classifier,vector<Rect>& faces){
    int rate = 4;
    int min_width = frame.size().width / rate;
    int min_height = frame.size().height / rate;
    Size min_size {min_width,min_height};

    Mat gray;
    cvtColor(frame,gray,COLOR_BGR2GRAY);
    classifier.detectMultiScale(gray,faces,1.3,detect_times,0,min_size);
    for(const auto & rect:faces){
        //rectangle(frame,rect,SCALAR_RED,tickness1);
        draw_ellipse(frame,rect);
    }
}

void on_bar_1(int arg,void*){
    if(arg >= 99)
        tickness1 = -1;
    else
        tickness1 = arg / 7;
    cout<<"tickness1:"<<tickness1<<endl;
}

void on_bar_2(int arg,void*){
    detect_times = arg/ 4;
    cout<<"detect_times:"<<detect_times<<endl;
}

int main(int argc, char const *argv[])
{

    bool is_closed = false;

    String wnd_name_1 {"wnd_1"};
    String wnd_name_2 {"wnd_2"};
    String ctl_wnd {"control_wnd"};
    namedWindow(ctl_wnd);

    String track_bar_name_1{"bar_1"};
    String track_bar_name_2 {"bar_2"};
    createTrackbar(track_bar_name_1,ctl_wnd,&tickness1,100,on_bar_1);
    createTrackbar(track_bar_name_2,ctl_wnd,&detect_times,100,on_bar_2);

    CascadeClassifier face_xml {file_face_xml_default};


    Mat buit_girl_1 = imread(face_file_11);

    while(!is_closed){

        imshow(wnd_name_1,buit_girl_1);
        Mat face = buit_girl_1.clone();
        vector<Rect> face_rects;
        detect_face(face,face_xml,face_rects);
        imshow(wnd_name_2,face);

        if(waitKey(150)>=0){
            is_closed = true;
        }
    }
    
    
    
    return 0;
}
