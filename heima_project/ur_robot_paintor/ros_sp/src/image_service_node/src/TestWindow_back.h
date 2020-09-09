#pragma once

#include <cv_bridge/cv_bridge.h>
#include <qlineedit.h>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <sensor_msgs/Image.h>

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QWidget>
#include <atomic>
#include <memory>

#include "Paintor.h"
#include "SimpleRobotMoveTask.h"
#include "SimpleSvgToWaysTask.h"
#include "actionlib/client/action_client.h"
#include "actionlib/client/client_helpers.h"
#include "my_robot_move_msgs/PainterMoveActionGoal.h"
#include "my_robot_move_msgs/Point.h"
#include "my_robot_move_msgs/RobotPoseInfoAction.h"
#include "my_robot_move_msgs/RobotPoseInfoFeedback.h"
#include "ros/node_handle.h"
#include "ros/subscriber.h"

class TestWindow : public QWidget {
    Q_OBJECT

    using _ActionClient_t =
        actionlib::ActionClient<my_robot_move_msgs::RobotPoseInfoAction>;

    using GoalHandle_t =
        actionlib::ClientGoalHandle<my_robot_move_msgs::RobotPoseInfoAction>;

    TestWindow();
    TestWindow(const TestWindow&) = delete;
    TestWindow operator=(const TestWindow&) = delete;

    ros::NodeHandle* node{nullptr};

    QLineEdit host_edit, port_edit;
    QPushButton connect_btn{"connect"}, disconnect_btn{"disconnect"};
    QLabel state_lab;

    QLineEdit pose_servername_edit{"ur_robot_pose_server"};
    QPushButton listenpose_btn{"listen pose"}, dislistenpose_btn{"dislisten"};
    QLabel pose_lab;

    QPushButton opencap_btn{"open capture"};
    QLineEdit topic_name_edit;
    QPushButton closecap_btn{"close capture"};

    SimpleSvgToWaysTask opensvg_task;
    QPushButton opensvg_btn{"open svg"};
    QLineEdit svgservername_edit;
    QLineEdit svgfilepath_edit;

    QLineEdit robot_move_action_server_name_edit{"ur_move_driver_server"};

    SimpleRobotMoveTask handdraw_task;
    QPushButton paint_handdraw_btn{"paint hand draw"};
    QPushButton dispaint_handdraw_btn{"break"};
    QProgressBar paint_handdraw_bar;

    SimpleSvgToWaysTask paint_svg_task;
    SimpleRobotMoveTask move_by_svg_task;
    QPushButton paint_svg_btn{"paint svg "};
    QPushButton dispaint_svg_btn{"break"};
    QProgressBar paint_svg_bar;

    QPushButton paint_camera_num_btn{"paint camera num"};
    QPushButton dispaint_camera_num_btn{"break"};
    QProgressBar paint_camera_num_bar;

    int paintor_width  = 500;
    int paintor_height = 400;
    Paintor paintor;

    QLineEdit sample_step_edit{"7"};
    QPushButton clean_paintor_btn{"clear"};
    QPushButton preview_paintor_btn{"preview"};

    QLineEdit a_edit{"0.14"}, v_edit{"0.25"}, epsilon_edit{"0.0124"};
    QLineEdit real_width_edit{"-0.4"}, real_height_edit{"0.2"};
    QLineEdit ori_pose_edit[6];
    QLineEdit tran_z_edit;

    QLabel info_lab;

    ros::Subscriber subscriber;

    std::shared_ptr<_ActionClient_t> pose_client;
    GoalHandle_t goal_handle;
    std::atomic_bool is_cancel_listen{false};

    void _init_virsual();
    void _init_event();

      protected:
    virtual ~TestWindow() {
    }

    static void simple_cap_test_callback(const sensor_msgs::ImageConstPtr& ptr);

    void on_tran_callback(GoalHandle_t);
    void on_feedback_callback(
        GoalHandle_t,
        my_robot_move_msgs::RobotPoseInfoFeedbackConstPtr);

    void set_handdraw_goal(my_robot_move_msgs::PainterMoveGoal&);

      public:
    static TestWindow& get_instance() {
        static TestWindow instance;
        return instance;
    }

    static QString loadQString(const QLineEdit& edit,
                               const QString& default_,
                               const QString& if_str = "") {
        auto&& t = edit.text().trimmed();
        return t == if_str ? default_ : t;
    }

    void set_node(ros::NodeHandle& node) {
        this->node                  = &node;
        this->handdraw_task.node    = this->node;
        this->opensvg_task.node     = this->node;
        this->move_by_svg_task.node = this->node;
        this->paint_svg_task.node   = this->node;
    }

    void get_half_info(my_robot_move_msgs::PainterMoveGoal&);
    void get_ori_pose(my_robot_move_msgs::Point& pose);

      signals:
    void info_out(const std::string&);
    void pose_out(const std::string&);

    void set_handdraw_bar(int);
    void set_paint_svg_bar(int);

      protected slots:
    void on_listen_pose();
    void on_dislisten_pose();
    void on_opencap();
    void on_info_out(const std::string&);
    void on_pose_out(const std::string&);

    void on_opensvg();

    void on_preview_handdraw();

    void on_paint_handdraw();

    void on_paint_svg();

    void on_set_handdraw_bar(int);
    void on_set_paint_svg_bar(int);
};
