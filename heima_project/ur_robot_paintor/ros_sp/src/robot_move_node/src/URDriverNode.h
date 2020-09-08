#pragma once

#include <actionlib/server/action_server.h>
#include <my_robot_move_msgs/PainterMoveAction.h>
#include <qobjectdefs.h>

#include <QObject>
#include <QTcpSocket>
#include <atomic>
#include <memory>
#include <mutex>

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

    GoalHandle_t goal_handle;

    QTcpSocket socket;
    double curren_pose[6];
    std::atomic_bool is_running{false};

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

    bool join_movel_util(const my_robot_move_msgs::Point& pnt, double epsilon);
    double error(const my_robot_move_msgs::Point& pnt);

      signals:
    void movel_to(float x,
                  float y,
                  float z,
                  float rx,
                  float ry,
                  float rz,
                  float a,
                  float v);
    void connect_socket_event();
    void connect_to_host();

      protected slots:

    void on_movel_to(float x,
                     float y,
                     float z,
                     float rx,
                     float ry,
                     float rz,
                     float a,
                     float v);
    void on_connected();
    void on_disconnected();
    void on_error();
    void on_readyread();
    void on_connect_socket_event();
    void on_connect_to_host();
};
