#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

String pic_dir {"/home/tad/Picture/"};

int main(int argc, char const *argv[])
{
    String file_path  { pic_dir+"/timg22.jpeg" };

    Mat src_o {imread(file_path)};
    Mat src = src_o.clone();

    uint8_t bias = 48;
    src = src + bias;

    Mat ch1,ch2,ch3;
    ch1.create(src.size(),CV_8UC1);
    ch2.create(src.size(),CV_8UC1);
    ch3.create(src.size(),CV_8UC1);

    extractChannel(src,ch1,0);
    extractChannel(src,ch2,1);
    extractChannel(src,ch3,2);

    String dst_wnd_name1 {"dst_wnd_1"};
    String dst_wnd_name2 {"dst_wnd_2"};
    String dst_wnd_name3 {"dst_wnd_3"};
    String src_wnd_name {"src_wnd"};
    imshow(src_wnd_name,src);
    imshow(dst_wnd_name1,ch1);
    imshow(dst_wnd_name2,ch2);
    imshow(dst_wnd_name3,ch3);

    waitKey();

    return 0;
}
