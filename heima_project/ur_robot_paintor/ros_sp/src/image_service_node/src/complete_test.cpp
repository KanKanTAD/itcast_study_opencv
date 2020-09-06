#include <ros/ros.h>

#include <QApplication>
#include <string>

#include "ros/init.h"

int main(int argc, char** argv) {
    std::string node_name{"complete_test_node"};
    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;

    ros::AsyncSpinner spinner{0};
    spinner.start();

    QApplication a(argc, argv);

    return a.exec();
}
