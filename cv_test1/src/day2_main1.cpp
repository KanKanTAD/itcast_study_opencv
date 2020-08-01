#include <iostream>
#include <opencv2/opencv.hpp>

cv::String pic_dir {"/home/tad/Picture/"};

void ma_shai_ke(const cv::Mat& src,int size,cv::Mat& res){
    int height = src.size().height;
    int width = src.size().width;

    for(int r=0;r<height;r+=size){
        for(int c=0;c<width;c+=size){
            auto h = r + size < height ? size : r+size - height;
            auto w = c + size < width ? size : c+size - width;
            cv::Rect rect {c,r,w,h};
            cv::Scalar sca = cv::sum(src(rect)) / (w*h);
            // cv::Vec3b v {src.at<cv::Vec3b>(r,c)};
            // cv::Scalar sca {v[0],v[1],v[2]};
            res(rect).setTo(sca);
        }
    }
}


void bian_li(const cv::Mat & src){
    auto channels = src.channels();
    auto nrow = src.rows;
    auto ncol = src.cols * channels;

    for(int r=0;r<nrow;r++){
        auto cols_pt = src.ptr<uint8_t>(r);
        std::cout<<"(";
        for(int c=0;c<ncol;c++){
            std::cout<<std::hex<<(int)cols_pt[c];
            if((0 != c) && (0 == c%3)){
                std::cout<<");(";
            }
        }
        std::cout<<std::endl;
    }
}

int main(int argc, char const *argv[])
{
    cv::String file_path1 {pic_dir + "timg13.jpeg"};

    auto src = cv::imread(file_path1);

    cv::String dst_wnd_name {"dst_wnd"};
    cv::String src_wnd_name {"src_wnd"};


    cv::Mat res { cv::Mat::zeros(src.size(),src.type()) };

    ma_shai_ke(src,64,res);
    //bian_li(src);
    cv::namedWindow(src_wnd_name);
    cv::namedWindow(dst_wnd_name);
    cv::imshow(src_wnd_name,src);
    cv::imshow(dst_wnd_name,res);

    cv::waitKey();

    return 0;
}
