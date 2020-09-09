#pragma once

#include <my_robot_move_msgs/SvgToPntss.h>
#include <ros/ros.h>

#include <QObject>
#include <chrono>
#include <functional>
#include <thread>

#include "MyTask.h"

class SimpleSvgToWaysTask : public MyTask {
    Q_OBJECT
      public:
    using Request_t = my_robot_move_msgs::SvgToPntssRequest;
    using Bean_t    = my_robot_move_msgs::SvgToPntss;

    std::function<void(Bean_t&)> on_successed_func = [](Bean_t&) {};
    std::function<void(int)> on_fail_func          = [](int) {};

    SimpleSvgToWaysTask() {
    }
    virtual ~SimpleSvgToWaysTask() {
    }

    static void _set_default_request_bean(Bean_t&);
    static bool _set_bean_pathd_by_filename0(Bean_t&, const std::string&);
    static bool _set_bean_pathd_by_filename1(Bean_t&, const std::string&);
    void run_goal(Bean_t&);
    virtual void cancel() override;
};
