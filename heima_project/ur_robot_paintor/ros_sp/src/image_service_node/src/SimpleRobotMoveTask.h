#pragma once

#include <actionlib/client/action_client.h>
#include <my_robot_move_msgs/PainterMoveAction.h>
#include <qobjectdefs.h>

#include <QObject>
#include <atomic>
#include <functional>
#include <memory>
#include <string>

#include "actionlib/client/client_helpers.h"
#include "my_robot_move_msgs/PainterMoveFeedback.h"
#include "my_robot_move_msgs/PainterMoveGoal.h"
#include "ros/node_handle.h"
class SimpleRobotMoveTask : public QObject {
    Q_OBJECT
      public:
    using ActionClient_t =
        actionlib::ActionClient<my_robot_move_msgs::PainterMoveAction>;

    using GoalHandle_t =
        actionlib::ClientGoalHandle<my_robot_move_msgs::PainterMoveAction>;

    GoalHandle_t goal_handle;

    std::function<void(GoalHandle_t)> tran_callback_func;
    std::function<void(GoalHandle_t,
                       my_robot_move_msgs::PainterMoveFeedbackConstPtr)>
        feedback_callback_func;

    std::shared_ptr<ActionClient_t> _client;
    // ActionClient_t* _client{nullptr};

    ros::NodeHandle* node{nullptr};
    std::string server_name;
    std::atomic_bool is_running{false};
    SimpleRobotMoveTask() = default;

    int send_goal(const my_robot_move_msgs::PainterMoveGoal& goal);

    void cancel();

    void on_tran_callback(GoalHandle_t handle);
    void on_feedback_callback(
        GoalHandle_t handle,
        my_robot_move_msgs::PainterMoveFeedbackConstPtr ptr);
};
