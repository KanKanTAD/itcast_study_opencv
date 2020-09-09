#include "URDriverNode.h"

#include <qobjectdefs.h>

#include <QAbstractSocket>
#include <QByteArray>
#include <QDataStream>
#include <chrono>
#include <cmath>
#include <complex>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include "MoveURDriver.h"
#include "SimpleURDriver.h"
#include "UR_Data.hpp"
#include "actionlib/server/server_goal_handle.h"
#include "my_robot_move_msgs/PainterMoveAction.h"
#include "my_robot_move_msgs/PainterMoveFeedback.h"
#include "my_robot_move_msgs/PainterMoveResult.h"
#include "my_robot_move_msgs/Point.h"
#include "ros/node_handle.h"

URDriverNode::URDriverNode(ros::NodeHandle& node,
                           const std::string& server_name)
    : node{node}, server_name{server_name} {
    qRegisterMetaType<
        actionlib::ServerGoalHandle<my_robot_move_msgs::PainterMoveAction>>(
        "GoalHandle_t");

    QObject::connect(this,
                     SIGNAL(create_task(GoalHandle_t)),
                     this,
                     SLOT(on_create_task(GoalHandle_t)));

    action_server.reset(new ActionServer_t(this->node, server_name, false));

    action_server->registerCancelCallback(boost::bind(
        &URDriverNode::cancel_callback, this, boost::placeholders::_1));
    action_server->registerGoalCallback(boost::bind(
        &URDriverNode::goal_callback, this, boost::placeholders::_1));
    action_server->start();
}

void URDriverNode::goal_callback(GoalHandle_t handle) {
    ROS_INFO_STREAM("got it");
    handle.setAccepted();
    qInfo() << "ways size:" << handle.getGoal()->ways.data.size() << __func__;
    emit create_task(handle);
}

void URDriverNode::cancel_callback(GoalHandle_t handle) {
    ROS_INFO_STREAM("cancel it");
    try {
        // handle.setCanceled();
        this->remove_task(handle);
    } catch (std::exception& e) {
        ROS_INFO_STREAM(e.what());
    }
}

void URDriverNode::remove_task(GoalHandle_t handle) {
    for (auto it = this->drivers.begin(); it != this->drivers.end(); it++) {
        if ((*it)->handle.getGoalID() == handle.getGoalID()) {
            //(*it)->handle.setCanceled();
            if ((*it)->is_connected) {
                emit(*it)->disconnect_from_host();
            } else {
                // this->drivers.erase(it);
            }
            return;
        }
    }
}

void URDriverNode::on_create_task(GoalHandle_t handle) {
    qInfo() << "ways size:" << handle.getGoal()->ways.data.size() << __func__;
    auto goal = handle.getGoal();
    qInfo() << "create task to ->" << tr(goal->host.c_str()) << ":"
            << goal->port;
    MoveURDriver::Ptr_t driver{new MoveURDriver(goal->host, goal->port)};
    driver->on_connected_func      = []() {};
    driver->on_goal_successed_func = [this, handle]() {
        this->remove_task(handle);
    };
    driver->on_goal_aborted_func = [this, handle]() {
        this->remove_task(handle);
    };
    this->drivers.push_back(driver);
    driver->run_goal0(handle);
}
