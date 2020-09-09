#include "SimpleRobotMoveTask.h"

#include <string>

#include "ros/duration.h"
#include "ros/node_handle.h"

int SimpleRobotMoveTask::run_goal(
    const my_robot_move_msgs::PainterMoveGoal& goal) {
    if (nullptr == node) {
        return -1;
    }
    this->_client.reset(new ActionClient_t(*node, server_name));
    if (!_client->waitForActionServerToStart(ros::Duration(5))) {
        return 1;
    }

    goal_handle = _client->sendGoal(
        goal,
        boost::bind(&SimpleRobotMoveTask::on_tran_callback,
                    this,
                    boost::placeholders::_1),
        boost::bind(&SimpleRobotMoveTask::on_feedback_callback,
                    this,
                    boost::placeholders::_1,
                    boost::placeholders::_2));
    return 0;
}
void SimpleRobotMoveTask::on_tran_callback(GoalHandle_t handle) {
    tran_callback_func(handle);
}
void SimpleRobotMoveTask::on_feedback_callback(
    GoalHandle_t handle,
    my_robot_move_msgs::PainterMoveFeedbackConstPtr ptr) {
    feedback_callback_func(handle, ptr);
}
void SimpleRobotMoveTask::cancel() {
    goal_handle.cancel();
}
