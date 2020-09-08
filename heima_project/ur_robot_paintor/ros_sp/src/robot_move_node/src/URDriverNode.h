#pragma once

#include <actionlib/server/action_server.h>
#include <my_robot_move_msgs/PainterMoveAction.h>

#include <QObject>
#include <QTcpSocket>
#include <atomic>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <utility>

#include "MoveURDriver.h"
#include "UR_Data.hpp"
#include "actionlib/server/server_goal_handle.h"
#include "my_robot_move_msgs/Point.h"
#include "ros/node_handle.h"

class URDriverNode : public QObject {
    Q_OBJECT

    std::once_flag __once;

      protected:
    using ActionServer_t =
        actionlib::ActionServer<my_robot_move_msgs::PainterMoveAction>;

    using GoalHandle_t =
        actionlib::ServerGoalHandle<my_robot_move_msgs::PainterMoveAction>;

    std::list<MoveURDriver::Ptr_t> drivers;

    ros::NodeHandle& node;

    std::shared_ptr<ActionServer_t> action_server;
    std::string server_name;

      public:
    URDriverNode(ros::NodeHandle&, const std::string&);

    virtual ~URDriverNode() {
    }

      protected:
    void goal_callback(GoalHandle_t);
    void cancel_callback(GoalHandle_t);

    void remove_task(GoalHandle_t);

      signals:

    void create_task(GoalHandle_t handle);
      protected slots:

    void on_create_task(GoalHandle_t handle);
};
