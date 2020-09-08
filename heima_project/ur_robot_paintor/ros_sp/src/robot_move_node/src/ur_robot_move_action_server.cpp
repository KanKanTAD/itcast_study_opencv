#include <actionlib/client/action_client.h>
#include <my_robot_move_msgs/PainterMoveAction.h>
#include <ros/ros.h>

#include <QApplication>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>
#include <thread>

#include "URDriverNode.h"
#include "my_robot_move_msgs/PainterMoveAction.h"
#include "my_robot_move_msgs/PainterMoveGoal.h"
#include "ros/init.h"
#include "ros/node_handle.h"
#include "ros/spinner.h"

int main(int argc, char** argv) {
    std::string node_name{"ur_robot_move_action_server_node"};
    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;

    ros::AsyncSpinner spinner{0};
    spinner.start();

    QApplication a{argc, argv};

    new std::thread([&]() {
        while (!ros::isShuttingDown()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(120));
        }
        a.quit();
    });

    URDriverNode ur_node(node, "ur_move_driver_server");

    return a.exec();
}
