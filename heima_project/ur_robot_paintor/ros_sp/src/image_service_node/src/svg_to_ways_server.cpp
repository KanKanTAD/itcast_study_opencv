#include <my_robot_move_msgs/SvgToPntss.h>
#include <ros/ros.h>

#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <string>

#include "about_svg_utils.hpp"
#include "my_robot_move_msgs/Point.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "ros/init.h"
#include "ros/node_handle.h"
#include "ros/spinner.h"

inline void setXYZ(my_robot_move_msgs::Point& pt, float x, float y, float z) {
    pt.x = x;
    pt.y = y;
    pt.z = z;
}
inline void setRPY(my_robot_move_msgs::Point& pt,
                   my_robot_move_msgs::SvgToPntssRequest& req) {
    pt.rx = req.rx;
    pt.ry = req.ry;
    pt.rz = req.rz;
}

bool server_callback(my_robot_move_msgs::SvgToPntssRequest& request,
                     my_robot_move_msgs::SvgToPntssResponse& response) {
    ROS_INFO_STREAM("I got it");
    std::vector<std::vector<cv::Point2i> > ways;
    for (auto& s : request.svg_pathds) {
        auto sp = utils::split(s);
        utils::get_way_from_pathd(*sp, ways);
    }

    my_robot_move_msgs::Point pnt;
    pnt.x = request.ori_x;
    pnt.y = request.ori_y;
    pnt.z = request.tran_z;
    setRPY(pnt, request);
    response.pts.data.push_back(pnt);
    float x, y, z;
    for (auto& way : ways) {
        for (auto& p : way) {
            x = p.x;
            x = x / request.svg_width * request.width + request.ori_x;
            y = p.y;
            y = y / request.svg_height * request.height + request.ori_y;
            z = request.ori_z;
            setXYZ(pnt, x, y, z);
            response.pts.data.push_back(pnt);
        }
        setXYZ(pnt, x, y, request.tran_z);
        response.pts.data.push_back(pnt);
    }

    return true;
}

int main(int argc, char** argv) {
    std::string node_name{"svg_to_ways_server_node"};
    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;

    // ros::AsyncSpinner spinner{0};
    // spinner.start();

    std::string server_name{"svg_to_ways_server"};
    auto server = node.advertiseService(server_name, server_callback);

    ros::spin();

    return 0;
}
