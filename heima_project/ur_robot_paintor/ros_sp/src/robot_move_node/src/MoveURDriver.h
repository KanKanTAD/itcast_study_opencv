#pragma once

#include <actionlib/server/action_server.h>
#include <my_robot_move_msgs/PainterMoveAction.h>

#include <functional>
#include <memory>

#include "SimpleURDriver.h"

class MoveURDriver : public SimpleURDriver {
    Q_OBJECT
      public:
    using Ptr_t = std::shared_ptr<MoveURDriver>;
    using GoalHandle_t =
        actionlib::ServerGoalHandle<my_robot_move_msgs::PainterMoveAction>;

    GoalHandle_t handle;

    std::function<void()> on_goal_successed_func = []() {};
    std::function<void()> on_goal_aborted_func   = []() {};
    std::function<void()> on_feedback_func       = []() {};

    static double angle_distance(double a, double b);
    static double movel_error(URData& data, my_robot_move_msgs::Point& pnt);
    static std::string get_movel_str(float x,
                                     float y,
                                     float z,
                                     float rx,
                                     float ry,
                                     float rz,
                                     float a,
                                     float v);

    MoveURDriver(const std::string& host, int port);
    MoveURDriver() : MoveURDriver("127.0.0.1", 30003) {
    }

    void run_goal0(GoalHandle_t);

      protected:
    int idx      = 0;
    int prev_idx = 0;

    void _set_driver_event();
    int run_next();
};
