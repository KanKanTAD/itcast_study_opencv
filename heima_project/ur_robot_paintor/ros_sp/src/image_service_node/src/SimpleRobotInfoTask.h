#pragma once

#include <actionlib/client/action_client.h>
#include <my_robot_move_msgs/RobotPoseInfoAction.h>

#include <chrono>
#include <functional>
#include <thread>

#include "MyTask.h"
#include "my_robot_move_msgs/RobotPoseInfoFeedback.h"
#include "my_robot_move_msgs/RobotPoseInfoGoal.h"

class SimpleRobotInfoTask : public MyTask {
    Q_OBJECT
      public:
    using ActionClient_t =
        actionlib::ActionClient<my_robot_move_msgs::RobotPoseInfoAction>;
    using GoalHandle_t =
        actionlib::ClientGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>;
    using Goal_t = my_robot_move_msgs::RobotPoseInfoGoal;

    std::shared_ptr<ActionClient_t> pose_client;
    GoalHandle_t goal_handle;
    std::function<void(GoalHandle_t handle,
                       my_robot_move_msgs::RobotPoseInfoFeedbackConstPtr ptr)>
        on_feedback_callback_func =
            [](GoalHandle_t handle,
               my_robot_move_msgs::RobotPoseInfoFeedbackConstPtr ptr) {};

    SimpleRobotInfoTask() {
    }
    virtual ~SimpleRobotInfoTask() {
    }

    virtual void cancel() override;

    int run_goal(Goal_t&);

      protected:
    void on_feedback_callback(
        GoalHandle_t handle,
        my_robot_move_msgs::RobotPoseInfoFeedbackConstPtr ptr);
};
