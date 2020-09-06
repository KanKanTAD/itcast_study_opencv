#include <geometry_msgs/PoseStamped.h>
#include <qcoreapplication.h>
#include <ros/ros.h>

#include <QApplication>
#include <QWidget>
#include <string>

#include "InfoWindow.h"
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

    InfoWindow wnd{};
    wnd.set_rosnode(node);
    wnd.set_publisher(publisher);

    return app.exec();
}
