#include <geometry_msgs/PoseStamped.h>
#include <qcoreapplication.h>
#include <qobjectdefs.h>
#include <ros/ros.h>

#include <QApplication>
#include <QWidget>
#include <chrono>
#include <string>
#include <thread>

#include "InfoWindow.h"
#include "SimpleURDriver.h"
#include "ros/console.h"
#include "ros/init.h"

int main(int argc, char** argv) {
    std::string node_name{"test_node"};

    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;

    ros::AsyncSpinner spinner{0};
    spinner.start();

    std::string publisher_name{"terminal_pose"};
    auto publisher =
        node.advertise<geometry_msgs::PoseStamped>(publisher_name, 1024);

    ROS_INFO_STREAM("hello world");

    QApplication app(argc, argv);
    new std::thread([&]() {
        while (ros::isShuttingDown() == false) {
            std::this_thread::sleep_for(std::chrono::milliseconds(120));
        }
        app.quit();
    });

    // SimpleURDriver driver{"127.0.0.1", 30003};
    // emit driver.connect_to_host();

    InfoWindow wnd{};
    wnd.set_rosnode(node);

    return app.exec();
}
