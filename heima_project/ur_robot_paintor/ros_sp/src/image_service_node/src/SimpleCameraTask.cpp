#include "SimpleCameraTask.h"

#include <cv_bridge/cv_bridge.h>

#include <exception>
#include <opencv2/highgui.hpp>

#include "sensor_msgs/Image.h"

int SimpleCameraTask::run_goal() {
    if (nullptr == node) {
        return -1;
    }
    try {
        subscriber.shutdown();
    } catch (std::exception& e) {
    }
    // this->subscriber = node->subscribe<sensor_msgs::Image>(
    // server_name, 1024, SimpleCameraTask::callback);
    this->subscriber = node->subscribe<sensor_msgs::Image>(
        server_name, 1024, [](sensor_msgs::ImageConstPtr ptr) {
            auto im =
                cv_bridge::toCvCopy(*ptr, sensor_msgs::image_encodings::BGR8);
            cv::imshow("info", im->image);
        });
    return 0;
}

void SimpleCameraTask::callback(sensor_msgs::ImageConstPtr ptr) {
    auto im = cv_bridge::toCvCopy(*ptr, sensor_msgs::image_encodings::BGR8);
    cv::imshow("info", im->image);
}

void SimpleCameraTask::cancel() {
    try {
        this->subscriber.shutdown();
        cv::destroyWindow("info");
    } catch (std::exception& e) {
    }
}
