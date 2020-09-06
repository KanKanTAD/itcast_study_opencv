#include <cv_bridge/cv_bridge.h>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <opencv2/opencv.hpp>
#include <string>

#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "ros/init.h"
#include "ros/rate.h"
#include "ros/spinner.h"
#include "ros/time.h"

int main(int argc, char** argv) {
    std::string node_name{"camera_info_node"};

    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;
    ros::AsyncSpinner spinner{0};
    spinner.start();

    auto publisher = node.advertise<sensor_msgs::Image>("camera_image", 1024);

    cv::VideoCapture cap{0};

    ros::Rate rate{30};

    while (ros::ok()) {
        cv::Mat frame;
        cap >> frame;

        cv::imshow("info", frame);

        cv_bridge::CvImage cvi;
        cvi.image           = frame;
        cvi.header.stamp    = ros::Time::now();
        cvi.header.frame_id = "camera_image";
        cvi.encoding        = "bgr8";

        sensor_msgs::Image im;
        cvi.toImageMsg(im);

        publisher.publish(im);
        rate.sleep();
        // cv::waitKey(30);
    }

    return 0;
}
