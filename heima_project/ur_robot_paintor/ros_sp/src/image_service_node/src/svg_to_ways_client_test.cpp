#include <my_robot_move_msgs/SvgToPntss.h>
#include <ros/ros.h>

#include <cstdio>
#include <iostream>

#include "about_svg_utils.hpp"

std::string file_dir{"/home/tad/Picture/svg_s/"};

int main(int argc, char** argv) {
    std::string node_name{"svg_to_ways_client_test_node"};
    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;

    std::string filepath = file_dir + "1.svg";
    if (argc >= 2) {
        filepath = argv[1];
    }

    std::string server_name{"svg_to_ways_server"};
    auto client =
        node.serviceClient<my_robot_move_msgs::SvgToPntss>(server_name);

    client.waitForExistence();
    my_robot_move_msgs::SvgToPntss obj;

    boost::property_tree::ptree pt;
    boost::property_tree::read_xml(filepath, pt);
    auto pathd = utils::get_pathd_from_doc(pt);

    auto sz                = utils::get_size_from_doc(pt);
    obj.request.ori_x      = -0.369;
    obj.request.ori_y      = -0.127;
    obj.request.ori_z      = 0.029;
    obj.request.rx         = 3.14;
    obj.request.ry         = 0.0;
    obj.request.rz         = 0.0;
    obj.request.tran_z     = 0.049;
    obj.request.width      = -0.4;
    obj.request.height     = 0.2;
    obj.request.svg_width  = sz.first;
    obj.request.svg_height = sz.second;
    obj.request.svg_pathds = *pathd;

    if (client.call(obj)) {
        char buff[1024];
        ROS_INFO_STREAM("response!");
        ROS_INFO_STREAM(obj.response.pts.data.size());
        for (auto& p : obj.response.pts.data) {
            std::sprintf(buff,
                         "%3.6f ,%3.6f ,%3.6f ,%3.6f ,%3.6f ,%3.6f\n",
                         p.x,
                         p.y,
                         p.z,
                         p.rx,
                         p.ry,
                         p.rz);
            // std::string arg = buff;
            ROS_INFO_STREAM(buff);
        }
    }

    ros::spin();

    return 0;
}
