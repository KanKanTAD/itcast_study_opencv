#pragma once

#include <actionlib/client/action_client.h>
#include <my_robot_move_msgs/PainterMoveAction.h>
#include <qobjectdefs.h>

#include <atomic>
#include <functional>
#include <memory>
#include <string>

#include "MyTask.h"
#include "actionlib/client/client_helpers.h"
#include "my_robot_move_msgs/PainterMoveFeedback.h"
#include "my_robot_move_msgs/PainterMoveGoal.h"
#include "ros/node_handle.h"
class SimpleRobotMoveTask : public MyTask {
    Q_OBJECT
      public:
    using ActionClient_t =
        actionlib::ActionClient<my_robot_move_msgs::PainterMoveAction>;

    using GoalHandle_t =
        actionlib::ClientGoalHandle<my_robot_move_msgs::PainterMoveAction>;

    GoalHandle_t goal_handle;

    std::function<void(GoalHandle_t)> tran_callback_func = [](GoalHandle_t) {};
    std::function<void(GoalHandle_t,
                       my_robot_move_msgs::PainterMoveFeedbackConstPtr)>
        feedback_callback_func =
            [](GoalHandle_t, my_robot_move_msgs::PainterMoveFeedbackConstPtr) {
            };

    std::shared_ptr<ActionClient_t> _client;
    // ActionClient_t* _client{nullptr};

    std::atomic_bool is_running{false};
    SimpleRobotMoveTask() = default;

    int run_goal(const my_robot_move_msgs::PainterMoveGoal& goal);

    virtual void cancel() override;

      protected:
    void on_tran_callback(GoalHandle_t handle);
    void on_feedback_callback(
        GoalHandle_t handle,
        my_robot_move_msgs::PainterMoveFeedbackConstPtr ptr);
};
