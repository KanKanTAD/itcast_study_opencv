#include <actionlib/client/action_client.h>
#include <my_robot_move_msgs/RobotPoseInfoAction.h>
#include <ros/ros.h>
#include <unistd.h>

#include <cstdio>
#include <string>

#include "actionlib/client/client_helpers.h"
#include "my_robot_move_msgs/RobotPoseInfoFeedback.h"
#include "my_robot_move_msgs/RobotPoseInfoGoal.h"
#include "ros/duration.h"
#include "ros/init.h"
#include "ros/rate.h"
#include "ros/spinner.h"

int main(int argc, char** argv) {
    std::string node_name{"robot_pose_action_client_test_node"};
    ROS_INFO_STREAM(node_name);

    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;
    ros::AsyncSpinner spinner{0};
    spinner.start();

    std::string server_name{"ur_robot_pose_server"};
    ROS_INFO_STREAM(server_name);
    actionlib::ActionClient<my_robot_move_msgs::RobotPoseInfoAction> client(
        node, server_name);

    ROS_INFO_STREAM("wait for action server to start()");
    client.waitForActionServerToStart();
    ROS_INFO_STREAM("end wait");
    if (client.isServerConnected() == false) {
        ROS_INFO_STREAM(server_name + " have no connected");
        return 0;
    }

    my_robot_move_msgs::RobotPoseInfoGoal goal;
    // goal.host = "192.168.36.26";
    goal.host = "127.0.0.1";
    goal.port = 30003;

    auto goal_handle = client.sendGoal(
        goal,
        [](actionlib::ClientGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>
               handle) { ROS_INFO_STREAM("trans it!"); },
        [](actionlib::ClientGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>
               handle,
           my_robot_move_msgs::RobotPoseInfoFeedbackConstPtr ptr) {
            ROS_INFO_STREAM("got feedback");
            auto& p = ptr->pose;
            char buff[1024];
            std::sprintf(buff,
                         "%3.6f ,%3.6f ,%3.6f ,%3.6f ,%3.6f ,%3.6f ",
                         p.x,
                         p.y,
                         p.z,
                         p.rx,
                         p.ry,
                         p.rz);
            ROS_INFO_STREAM(buff);
        });
    ros::Rate rate{60};
    while (ros::isShuttingDown() == false) {
        rate.sleep();
    }
    return 0;
}
