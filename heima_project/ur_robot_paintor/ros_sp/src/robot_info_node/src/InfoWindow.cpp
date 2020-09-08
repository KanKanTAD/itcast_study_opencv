#include "InfoWindow.h"

#include <qlabel.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <tf/transform_datatypes.h>

#include <QGridLayout>

#include "actionlib/client/action_client.h"
#include "actionlib/client/client_helpers.h"
#include "actionlib/client/comm_state.h"
#include "actionlib/client/terminal_state.h"
#include "geometry_msgs/PoseStamped.h"
#include "my_robot_move_msgs/RobotPoseInfoAction.h"
#include "my_robot_move_msgs/RobotPoseInfoFeedback.h"
#include "my_robot_move_msgs/RobotPoseInfoGoal.h"
#include "ros/duration.h"
#include "tf/LinearMath/Quaternion.h"

InfoWindow::InfoWindow(QWidget* ptr) : QWidget(ptr) {
    auto* main_layout = new QGridLayout{this};

    main_layout->addWidget(
        new QLabel{"host:"}, 0, 0, Qt::AlignmentFlag::AlignRight);
    this->ip_edit.setText("192.168.36.26");
    main_layout->addWidget(&this->ip_edit, 0, 1, Qt::AlignmentFlag::AlignLeft);
    main_layout->addWidget(
        new QLabel{":"}, 0, 2, Qt::AlignmentFlag::AlignCenter);
    this->port_edit.setText("30003");
    main_layout->addWidget(&this->port_edit, 0, 3, Qt::AlignLeft);

    main_layout->addWidget(
        &this->action_server_name_edit, 1, 0, 1, 4, Qt::AlignRight);

    main_layout->addWidget(&this->disconnect_btn, 2, 0, Qt::AlignLeft);
    main_layout->addWidget(&this->connect_btn, 2, 3, Qt::AlignRight);

    const char* names[] = {"x:", "y:", "z:", "rx:", "ry:", "rz:"};
    for (int i = 0; i < 6; i++) {
        main_layout->addWidget(
            new QLabel{names[i]}, 3 + i, 0, 1, 1, Qt::AlignRight);
        main_layout->addWidget(
            &this->pose_lab[i], 3 + i, 1, 1, 3, Qt::AlignLeft);
    }

    this->show();

    QObject::connect(
        &connect_btn, SIGNAL(clicked()), this, SLOT(on_connect_btn()));

    QObject::connect(
        &disconnect_btn, SIGNAL(clicked()), this, SLOT(on_disconnect_btn()));
}

void InfoWindow::on_connect_btn() {
    ROS_INFO_STREAM("on connected!!");
    client.reset(
        new actionlib::ActionClient<my_robot_move_msgs::RobotPoseInfoAction>(
            *node, action_server_name_edit.text().toStdString()));
    if (!client->waitForActionServerToStart(ros::Duration(5))) {
        ROS_INFO_STREAM("server no start?");
        return;
    }
    my_robot_move_msgs::RobotPoseInfoGoal goal;
    goal.host = this->ip_edit.text().toStdString();
    goal.port = this->port_edit.text().toInt();
    ROS_INFO_STREAM("send goal...");
    goal_handle = client->sendGoal(
        goal,
        [](actionlib::ClientGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>
               handle) {
            ROS_INFO_STREAM("tran it");

            if (handle.getCommState() == actionlib::CommState::ACTIVE) {
                ROS_INFO_STREAM("active!!");
            } else if (handle.getCommState() == actionlib::CommState::PENDING) {
                ROS_INFO_STREAM("pending!!");
            } else if (handle.getCommState() ==
                       actionlib::CommState::RECALLING) {
                ROS_INFO_STREAM("recalling!!");
            } else if (handle.getCommState() ==
                       actionlib::CommState::PREEMPTING) {
                ROS_INFO_STREAM("preempting!!");
            } else if (handle.getCommState() == actionlib::CommState::DONE) {
                if (handle.getTerminalState() ==
                    actionlib::TerminalState::ABORTED) {
                    ROS_INFO_STREAM("aborted!");
                } else if (handle.getTerminalState() ==
                           actionlib::TerminalState::REJECTED) {
                    ROS_INFO_STREAM("rejected!");
                } else if (handle.getTerminalState() ==
                           actionlib::TerminalState::PREEMPTED) {
                    ROS_INFO_STREAM("preempts!");
                } else if (handle.getTerminalState() ==
                           actionlib::TerminalState::RECALLED) {
                    ROS_INFO_STREAM("recalled!");
                }
            }
        },
        [this](
            actionlib::ClientGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>
                handle,
            my_robot_move_msgs::RobotPoseInfoFeedbackConstPtr ptr) {
            auto pose = ptr->pose;
            this->pose_lab[0].setText(QString::number(pose.x));
        });
}

void InfoWindow::on_disconnect_btn() {
    goal_handle.cancel();
}
