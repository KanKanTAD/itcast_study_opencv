#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

using namespace cv;

String haar_cascades_dir {"/usr/share/opencv4/haarcascades/"};
String path_default_face_xml {haar_cascades_dir + "haarcascade_frontalface_default.xml"};

const Scalar SCALAR_RED {16,16,128};
int value_bar1;

int tickness1=1;

vector<Rect> detectAndDraw(Mat & ,CascadeClassifier&,int count=5);
static void on_bar1(int,void*);


int main() {
    String ctr_wnd_name {"control_wnd"};
    namedWindow(ctr_wnd_name);

    String track_bar_name1 {"track_bar1"};
    createTrackbar(track_bar_name1,ctr_wnd_name,&value_bar1,100,on_bar1);


    CascadeClassifier face_xml(path_default_face_xml);
    if(face_xml.empty()){
        cout<<"face_xml is not fond!!!"<<endl;
        return 2;
    }

    VideoCapture cap {0};
    if(!cap.isOpened()){
        cout<<"video capture open false!!!"<<endl;
        return 1;
    }

    bool closed = false;
    String main_wnd_name {"main_wnd"};
    String detect_wnd_name {"detect_wnd"};

    Mat frame;
    while(!closed){
        cap >> frame;
        imshow(main_wnd_name,frame);

        Mat face = frame.clone();
        detectAndDraw(face,face_xml);

        imshow(detect_wnd_name,face);

        if(waitKey(150)>=0){
            closed = true;
        }
    }

    return 0;
}

vector<Rect> detectAndDraw(Mat& frame,CascadeClassifier& classifier,int count){
    int min_width = frame.size().width / 3;
    int min_height = frame.size().height / 3;

    Mat gray;
    cvtColor(frame,gray,COLOR_BGR2GRAY);
    vector<Rect> faces;
    classifier.detectMultiScale(gray,faces,1.1,count,
        0,Size{min_width,min_height});
    cout<<"found count of face:"<<faces.size()<<endl;
    for(const auto& rect:faces){
        //rectangle(frame,rect,SCALAR_RED,tickness1);
        Point center {rect.x + rect.width/2,rect.y+rect.height/2};
        ellipse(frame,center,Size{rect.width/2,rect.height/2},0,0,360,SCALAR_RED,tickness1);
    }

    return faces;
}


void on_bar1(int bar_value,void*){

    tickness1 = bar_value / 7;
    cout<<tickness1<<endl;

}