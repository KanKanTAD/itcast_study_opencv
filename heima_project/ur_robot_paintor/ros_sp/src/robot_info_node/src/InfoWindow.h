#pragma once

#include <actionlib/client/action_client.h>
#include <my_robot_move_msgs/RobotPoseInfoAction.h>
#include <qlineedit.h>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QWidget>
#include <memory>

#include "UR_Data.hpp"
#include "actionlib/client/client_helpers.h"
#include "ros/node_handle.h"
#include "ros/publisher.h"

class InfoWindow : public QWidget {
    Q_OBJECT

      public:
    virtual ~InfoWindow() {
    }
    InfoWindow(QWidget* ptr = nullptr);

    void set_rosnode(ros::NodeHandle& node) {
        this->node = &node;
    }

      private:
    ros::NodeHandle* node{nullptr};
    std::shared_ptr<
        actionlib::ActionClient<my_robot_move_msgs::RobotPoseInfoAction>>
        client;
    actionlib::ClientGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>
        goal_handle;

    QPushButton connect_btn{"connect"}, disconnect_btn{"disconnect"};
    QLineEdit action_server_name_edit{"ur_robot_pose_server"};
    QLineEdit ip_edit, port_edit;
    QLabel pose_lab[6];
    QTcpSocket socket;

      protected slots:
    void on_connect_btn();
    void on_disconnect_btn();
};
