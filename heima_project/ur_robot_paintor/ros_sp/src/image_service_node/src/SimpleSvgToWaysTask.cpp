#include "SimpleSvgToWaysTask.h"

#include "about_svg_utils.hpp"

void SimpleSvgToWaysTask::_set_default_request_bean(Bean_t& obj) {
    obj.request.ori_x  = 0;
    obj.request.ori_y  = 0;
    obj.request.ori_z  = 0.029;
    obj.request.rx     = 3.14;
    obj.request.ry     = 0.0;
    obj.request.rz     = 0.0;
    obj.request.tran_z = 0.049;
}

bool SimpleSvgToWaysTask::_set_bean_pathd_by_filename0(
    Bean_t& obj,
    const std::string& file_path) {
    boost::property_tree::ptree pt;
    try {
        boost::property_tree::read_xml(file_path, pt);
    } catch (std::exception& e) {
        return false;
    }
    auto pathd             = utils::get_pathd_from_doc(pt);
    auto sz                = utils::get_size_from_doc(pt);
    obj.request.svg_width  = sz.first;
    obj.request.svg_height = sz.second;
    obj.request.svg_pathds = *pathd;
    return true;
}

bool SimpleSvgToWaysTask::_set_bean_pathd_by_filename1(
    Bean_t& obj,
    const std::string& file_path) {
    boost::property_tree::ptree pt;
    try {
        boost::property_tree::read_xml(file_path, pt);
    } catch (std::exception& e) {
        return false;
    }
    auto pathd             = utils::get_pathd_from_doc(pt);
    auto sz                = utils::get_size_from_doc(pt);
    obj.request.width      = sz.first;
    obj.request.height     = sz.second;
    obj.request.svg_width  = sz.first;
    obj.request.svg_height = sz.second;
    obj.request.svg_pathds = *pathd;
    return true;
}

void SimpleSvgToWaysTask::run_goal(Bean_t& bean) {
    new std::thread([this, bean]() mutable {
        auto client =
            node->serviceClient<my_robot_move_msgs::SvgToPntss>(server_name);

        if (!client.waitForExistence(ros::Duration(5))) {
            this->on_fail_func(-1);
            return;
        }

        auto& obj = bean;

        if (client.call(obj)) {
            this->on_successed_func(obj);
        }
        client.shutdown();
    });
}

void SimpleSvgToWaysTask::cancel() {
    return;
}
