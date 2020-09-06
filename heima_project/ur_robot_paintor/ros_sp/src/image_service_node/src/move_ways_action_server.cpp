#include <actionlib/server/action_server.h>
#include <my_robot_move_msgs/PainterMoveAction.h>
#include <ros/ros.h>

#include <string>

int main(int argc, char** argv) {
    std::string node_name{"move_ways_action_server_node"};

    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;

    std::string server_name{"move_ways_action_server"};
    actionlib::ActionServer<my_robot_move_msgs::PainterMoveAction>
        action_server(node, server_name, false);

    ros::spin();
    return 0;
}
