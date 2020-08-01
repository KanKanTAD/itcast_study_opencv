#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

String pic_dir {"/home/tad/Picture/"};

void my_extraChannels(const Mat& src,Mat (&channels)[3]){
    for(int i=0;i<3;i++){
        extractChannel(src,channels[i],i);
    }
}
void my_equalHist(const Mat& src,Mat &dst,float (&w)[3]){
    Mat channels[3];
    my_extraChannels(src,channels);

    Mat out_channels[3];
    for(int i=0;i<3;i++){
        equalizeHist(channels[i],out_channels[i]);
        out_channels[i] *= w[i];
    }


    merge(out_channels,3,dst);
}

int main(int argc, char const *argv[])
{

    auto pic = imread(pic_dir+"timg31.jpeg");
    auto pic2 = imread(pic_dir+"timg13.jpeg");

    int scale = 3;
    auto width = pic.size().width / scale;
    auto height = pic.size().height / scale;

    Size sz {width,height};

    Mat pic1;
    resize(pic,pic1,sz);

    Mat pic3;
    resize(pic2,pic3,sz);

    cout<<pic1.type()<<";"<<pic1.size()<<endl;

    VideoCapture cap {0};
    Mat frame;
    bool no_stop = true;
    String wnd_name {"video_current"};
    String dst_wnd_name {"good_wnd"};
    String dst_wnd_name1{"good_wnd1"};
    String dst_wnd_name2 {"good_wnd2"};

    float w[3] = {0.5f,0.3f,0.2f};
    double alpha = 0.86;
    double beta=0.14;
    double gamma = 3.7;


    Mat pic4;

    pic4 = pic1*alpha + pic3*beta + gamma;
    imshow(dst_wnd_name2,pic4);

    bool once = true;
    while(no_stop){
        cap>>frame;
        Mat good;
        my_equalHist(frame,good,w);
        auto good1 = frame.clone();
        good1.resize(height,width);

        Mat good2;
        resize(frame,good2,sz);

        if(once){
            cout<<good2.type()<<";"<<good2.size()<<endl;
            once = false;
        }
        Mat good3;
        addWeighted(good2,alpha,pic3,beta,gamma,good3);
        imshow(wnd_name,frame);
        imshow(dst_wnd_name,good);
        imshow(dst_wnd_name1,good3);

        if(waitKey(150) >= 0){
            no_stop = false;
        }
    }

}