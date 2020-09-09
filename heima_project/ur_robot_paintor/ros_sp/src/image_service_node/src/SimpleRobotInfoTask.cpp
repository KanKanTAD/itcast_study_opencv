#include "SimpleRobotInfoTask.h"

#include "ros/duration.h"

void SimpleRobotInfoTask::cancel() {
    this->goal_handle.cancel();
}

int SimpleRobotInfoTask::run_goal(Goal_t& goal) {
    if (nullptr == node) {
        return -1;
    }
    this->pose_client.reset(new ActionClient_t(*node, this->server_name));
    if (!pose_client->waitForActionServerToStart(ros::Duration(2))) {
        return -2;
    }
    new std::thread([this, goal]() {
        this->goal_handle = pose_client->sendGoal(
            goal,
            [](GoalHandle_t handle) { ROS_INFO_STREAM("tran it!"); },
            boost::bind(&SimpleRobotInfoTask::on_feedback_callback,
                        this,
                        boost::placeholders::_1,
                        boost::placeholders::_2));
    });
    return 0;
}

void SimpleRobotInfoTask::on_feedback_callback(
    GoalHandle_t handle,
    my_robot_move_msgs::RobotPoseInfoFeedbackConstPtr ptr) {
    this->on_feedback_callback_func(handle, ptr);
}
