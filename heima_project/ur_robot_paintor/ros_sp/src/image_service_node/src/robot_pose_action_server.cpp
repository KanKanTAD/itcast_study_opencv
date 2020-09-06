#include <actionlib/server/action_server.h>
#include <my_robot_move_msgs/RobotPoseInfoAction.h>
#include <qcoreapplication.h>
#include <qtcpsocket.h>
#include <ros/ros.h>
#include <unistd.h>

#include <QApplication>
#include <QString>
#include <QTcpSocket>
#include <QWidget>
#include <chrono>
#include <cstdlib>
#include <string>
#include <thread>

#include "my_robot_move_msgs/RobotPoseInfoGoal.h"
#include "ros/init.h"
#include "ros/spinner.h"

void goal_callback(
    actionlib::ServerGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>
        handle) {
    ROS_INFO_STREAM("got it");
    handle.setAccepted();
}

void cancel_callback(
    actionlib::ServerGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>
        handle) {
    handle.setCanceled();
}

int main(int argc, char** argv) {
    std::string node_name{"robot_pose_action_server_node"};
    ROS_INFO_STREAM(node_name);

    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;
    ros::AsyncSpinner spinner{0};
    spinner.start();

    std::string server_name{"abcd"};
    ROS_INFO_STREAM(server_name);
    actionlib::ActionServer<my_robot_move_msgs::RobotPoseInfoAction>
        action_server{node, server_name, false};

    action_server.registerGoalCallback(
        boost::bind(goal_callback, boost::placeholders::_1));
    action_server.registerCancelCallback(
        boost::bind(cancel_callback, boost::placeholders::_1));
    action_server.start();
    ROS_INFO_STREAM(server_name + " are going");

    QCoreApplication app{argc, argv};
    new std::thread([&]() {
        while (ros::isShuttingDown() == false) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        app.quit();
    });

    return app.exec();
}
