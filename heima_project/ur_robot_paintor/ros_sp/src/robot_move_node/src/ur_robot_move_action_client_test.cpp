#include <actionlib/client/action_client.h>
#include <my_robot_move_msgs/PainterMoveAction.h>
#include <ros/ros.h>

#include <QApplication>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "my_robot_move_msgs/Point.h"
#include "ros/init.h"
#include "ros/node_handle.h"
#include "ros/spinner.h"

int main(int argc, char** argv) {
    std::string node_name{"ur_robot_move_action_client_test_node"};
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

    actionlib::ActionClient<my_robot_move_msgs::PainterMoveAction> client(
        node, "ur_move_driver_server");

    client.waitForActionServerToStart();

    my_robot_move_msgs::PainterMoveGoal goal;
    goal.host    = "127.0.0.1";
    goal.port    = 30003;
    goal.epsilon = 0.01;
    my_robot_move_msgs::Point pnt;
    pnt.x  = 0.1;
    pnt.y  = 0.1;
    pnt.z  = 0.1;
    pnt.rx = 0.1;
    pnt.ry = 0.1;
    pnt.rz = 0.1;
    goal.ways.data.push_back(pnt);
    pnt.x  = 0.2;
    pnt.y  = 0.2;
    pnt.z  = 0.2;
    pnt.rx = 0.2;
    pnt.ry = 0.2;
    pnt.rz = 0.2;
    goal.ways.data.push_back(pnt);

    auto goal_handle = client.sendGoal(
        goal,
        [](actionlib::ClientGoalHandle<my_robot_move_msgs::PainterMoveAction>
               handle) { ROS_INFO_STREAM("tran it"); },

        [](actionlib::ClientGoalHandle<my_robot_move_msgs::PainterMoveAction>
               handle,
           my_robot_move_msgs::PainterMoveFeedbackConstPtr ptr) {
            char buff[1024];
            sprintf(buff,
                    "%3.3f,%3.3f,%3.3f --- %3.3f",
                    ptr->current_pose.x,
                    ptr->current_pose.y,
                    ptr->current_pose.z,
                    ptr->percent);
            ROS_INFO_STREAM(buff);
        });
    return a.exec();
}
