#include <ros/ros.h>

#include <string>

#include "cv_bridge/cv_bridge.h"
#include "opencv2/highgui.hpp"
#include "ros/init.h"
#include "ros/node_handle.h"
#include "ros/rate.h"
#include "ros/spinner.h"
#include "ros/subscriber.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/image_encodings.h"

void call_back(const sensor_msgs::ImageConstPtr& ptr) {
    // ROS_INFO_STREAM("I got it");
    auto im = cv_bridge::toCvCopy(*ptr, sensor_msgs::image_encodings::BGR8);
    cv::imshow("info", im->image);
    cv::waitKey(30);
}

int main(int argc, char** argv) {
    std::string node_name{"camera_image_listen"};
    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);
    ros::NodeHandle node;

    ros::AsyncSpinner spinner{0};
    spinner.start();

    std::string topic_name{"camera_image"};
    ros::Subscriber subscriber =
        node.subscribe<sensor_msgs::Image>(topic_name, 1024, call_back);

    ros::Rate rate{30};
    while (ros::ok()) {
        rate.sleep();
    }
    return 0;
}
