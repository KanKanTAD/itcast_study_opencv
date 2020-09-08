#pragma once

#include <actionlib/server/action_server.h>
#include <my_robot_move_msgs/RobotPoseInfoAction.h>
#include <qcoreapplication.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qtcpsocket.h>
#include <ros/ros.h>
#include <unistd.h>

#include <QApplication>
#include <QString>
#include <QTcpSocket>
#include <QWidget>
#include <chrono>
#include <cstdlib>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "SimpleURDriver.h"
#include "UR_Data.hpp"
#include "actionlib/server/server_goal_handle.h"
#include "my_robot_move_msgs/RobotPoseInfoFeedback.h"
#include "my_robot_move_msgs/RobotPoseInfoGoal.h"
#include "ros/init.h"
#include "ros/spinner.h"

class RobotPoseActionServer : public QObject {
    Q_OBJECT

    using GoalHandle_t =
        actionlib::ServerGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>;

    using _ActionServer_t =
        actionlib::ActionServer<my_robot_move_msgs::RobotPoseInfoAction>;

    std::list<std::pair<GoalHandle_t, SimpleURDriver::Ptr_t>>
        handle_and_driver_s;

    std::string server_name;
    ros::NodeHandle& node;

    std::shared_ptr<_ActionServer_t> action_server;

      public:
    RobotPoseActionServer(const std::string& server_name,
                          ros::NodeHandle& node);

    virtual ~RobotPoseActionServer() {
    }

      protected:
    void goal_callback(GoalHandle_t handle);

    void cancel_callback(GoalHandle_t handle);

    void _set_ur_driver_event(SimpleURDriver::Ptr_t, GoalHandle_t);

    void remove_from_handle_and_driver_s(GoalHandle_t);

      signals:
    void create_task(GoalHandle_t);
      protected slots:
    void on_create_task(GoalHandle_t);
};
