#include "RobotPoseActionServer.h"

#include <qobject.h>
#include <qobjectdefs.h>

#include <mutex>

#include "SimpleURDriver.h"
#include "UR_Data.hpp"
#include "my_robot_move_msgs/RobotPoseInfoAction.h"

RobotPoseActionServer::RobotPoseActionServer(const std::string& server_name,
                                             ros::NodeHandle& node)
    : server_name{server_name}, node{node} {
    qRegisterMetaType<
        actionlib::ServerGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>>(
        "GoalHandle_t");

    QObject::connect(this,
                     SIGNAL(create_task(GoalHandle_t)),
                     this,
                     SLOT(on_create_task(GoalHandle_t)));

    action_server.reset(new _ActionServer_t{node, server_name, false});

    action_server->registerGoalCallback(boost::bind(
        &RobotPoseActionServer::goal_callback, this, boost::placeholders::_1));
    action_server->registerCancelCallback(
        boost::bind(&RobotPoseActionServer::cancel_callback,
                    this,
                    boost::placeholders::_1));
    action_server->start();
}
void RobotPoseActionServer::goal_callback(GoalHandle_t handle) {
    ROS_INFO_STREAM("got it");
    handle.setAccepted();
    ROS_INFO_STREAM("accepted");
    emit this->create_task(handle);
}

void RobotPoseActionServer::_set_ur_driver_event(SimpleURDriver::Ptr_t driver,
                                                 GoalHandle_t handle) {
    // ROS_INFO_STREAM("_set_ur_driver_event");
    driver->on_connected_func    = []() mutable {};
    driver->on_disconnected_func = [handle]() mutable { handle.setAborted(); };
    driver->on_error_func        = [this,
                             handle](QAbstractSocket::SocketError) mutable {
        handle.setAborted();
        remove_from_handle_and_driver_s(handle);
    };
    driver->on_readyread_func = [driver, handle]() mutable {
        auto& data = driver->ur_data;
        my_robot_move_msgs::RobotPoseInfoFeedback feedback;
        feedback.code    = 200;
        feedback.info    = "ok!";
        feedback.pose.x  = data.Tool_vector_actual[0];
        feedback.pose.y  = data.Tool_vector_actual[1];
        feedback.pose.z  = data.Tool_vector_actual[2];
        feedback.pose.rx = data.Tool_vector_actual[3];
        feedback.pose.ry = data.Tool_vector_actual[4];
        feedback.pose.rz = data.Tool_vector_actual[5];
        handle.publishFeedback(feedback);
    };
}

void RobotPoseActionServer::cancel_callback(GoalHandle_t handle) {
    ROS_INFO_STREAM("cancel!");
    // handle.setCanceled();
    remove_from_handle_and_driver_s(handle);
}
void RobotPoseActionServer::remove_from_handle_and_driver_s(
    GoalHandle_t handle) {
    for (auto it = this->handle_and_driver_s.begin();
         it != this->handle_and_driver_s.end();
         it++) {
        if (it->first.getGoalID() == handle.getGoalID()) {
            emit it->second->disconnect_from_host();
            this->handle_and_driver_s.erase(it);
            return;
        }
    }
}

void RobotPoseActionServer::on_create_task(GoalHandle_t handle) {
    auto goal = handle.getGoal();
    SimpleURDriver::Ptr_t driver{new SimpleURDriver{goal->host, goal->port}};
    driver->setParent(this);
    _set_ur_driver_event(driver, handle);
    this->handle_and_driver_s.push_back({handle, driver});
    // emit driver->connect_to_host();
    driver->_connect_to_host();
    ROS_INFO_STREAM(" wait connected successed");
}
