#include <iostream>
#include <libfreenect2/libfreenect2.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    cv::String wnd_name_1{" src_window 1"};
    cv::namedWindow(wnd_name_1);
    while (true) {
        auto action = cv::waitKey(30) & 0xff;

        if ('\x20' == action) {
            std::cout << "customer saved the pictrue!!" << std::endl;
        } else if ('\x1b' == action) {
            break;
        }
    }
    return 0;
}
