#include <iostream>
#include <opencv2/imgproc.hpp>

#include "about_svg_utils.hpp"

std::string svg_dir{
    "/home/tad/Public/itcast_study_opencv/heima_project/robot_paintor/cpp/"
    "paint_svg/svg_res/"};

void test_draw_svg(const std::string& name) {
    boost::property_tree::ptree pt;
    std::vector<boost::property_tree::ptree> paths;

    try {
        boost::property_tree::ptree pt;
        boost::property_tree::read_xml(svg_dir + name, pt);
        auto size = utils::get_size_from_svg(pt.get_child("svg"));
        std::cout << "width:" << size.first << " ,height:" << size.second
                  << std::endl;

        auto paths = utils::get_paths_from_svg(pt);
        // for (auto& el : *paths) {
        // std::cout << el.get<std::string>("<xmlattr>.d") << std::endl;
        //}

        auto ways = utils::get_ways_form_paths(*paths);
        std::cout << "ways.size():" << ways->size() << std::endl;
        cv::Mat pic = cv::Mat::zeros(size.second, size.first, CV_8UC1);
        for (auto& way : *ways) {
            for (int i = 1; i < way.size(); i++) {
                cv::line(pic, way.at(i - 1), way.at(i), cv::Scalar::all(255.0));
            }
        }

        cv::imshow("info", pic);
        cv::waitKey(0);

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void test_lina() {
    auto sp = utils::linspace(0, 1, 101);
    std::cout << "size:" << sp->size() << std::endl;
    for (auto& v : *sp) {
        std::cout << v << std::endl;
    }
}

int main(int argc, char** argv) {
    std::string name{"zh.svg"};
    if (argc >= 2) {
        name = argv[1];
    }
    // test_lina();
    test_draw_svg(name);
    return 0;
}
