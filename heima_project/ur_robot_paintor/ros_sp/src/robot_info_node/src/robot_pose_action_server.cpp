#include <actionlib/server/action_server.h>
#include <my_robot_move_msgs/RobotPoseInfoAction.h>
#include <qcoreapplication.h>
#include <qobject.h>
#include <qtcpsocket.h>
#include <ros/ros.h>
#include <unistd.h>

#include <QApplication>
#include <QString>
#include <QTcpSocket>
#include <QWidget>
#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include <thread>

#include "RobotPoseActionServer.h"
#include "UR_Data.hpp"
#include "actionlib/server/server_goal_handle.h"
#include "my_robot_move_msgs/RobotPoseInfoFeedback.h"
#include "my_robot_move_msgs/RobotPoseInfoGoal.h"
#include "ros/init.h"
#include "ros/spinner.h"

int main(int argc, char** argv) {
    std::string node_name{"robot_pose_action_server_node"};
    ROS_INFO_STREAM(node_name);

    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;
    ros::AsyncSpinner spinner{0};
    spinner.start();

    QCoreApplication app{argc, argv};

    RobotPoseActionServer server{"ur_robot_pose_server", node};

    new std::thread([&]() {
        while (ros::isShuttingDown() == false) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        app.quit();
    });

    return app.exec();
}
