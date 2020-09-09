#pragma once
#include <actionlib/client/action_client.h>
#include <my_robot_move_msgs/RobotPoseInfoAction.h>

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QProgressBar>
#include <QPushButton>
#include <QWidget>
#include <atomic>
#include <memory>
#include <opencv2/opencv.hpp>

#include "Paintor.h"
#include "SimpleCameraTask.h"
#include "SimpleRobotInfoTask.h"
#include "SimpleRobotMoveTask.h"
#include "SimpleSvgToWaysTask.h"

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

    SimpleRobotInfoTask robot_pose_task;
    QLineEdit pose_servername_edit{"ur_robot_pose_server"};
    QPushButton listenpose_btn{"listen pose"}, dislistenpose_btn{"dislisten"};
    QLabel pose_lab;

    SimpleCameraTask camera_task;
    QPushButton opencap_btn{"open capture"};
    QLineEdit topic_name_edit;
    QPushButton closecap_btn{"close capture"};

    SimpleSvgToWaysTask svg_to_ways_task;
    QPushButton opensvg_btn{"open svg"};
    QLineEdit svgservername_edit;
    QLineEdit svgfilepath_edit;

    QLineEdit robot_move_action_server_name_edit{"ur_move_driver_server"};

    SimpleRobotMoveTask hanndraw_task;
    QPushButton paint_handdraw_btn{"paint hand draw"};
    QPushButton dispaint_handdraw_btn{"break"};
    QProgressBar paint_handdraw_bar;

    SimpleRobotMoveTask svg_paint_task;
    SimpleSvgToWaysTask svg_to_ways_paint_task;
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

    void _init_virsual();
    void _init_event();
    void _init_about_svg_event();
    void _init_about_handdraw_event();
    void _init_about_paint_svg_event();

      protected:
    void get_half_info(my_robot_move_msgs::PainterMoveGoal&);
    void get_ori_pose(my_robot_move_msgs::Point& pose);
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

    void set_node(ros::NodeHandle&);
    virtual ~TestWindow() {
    }

      signals:
    void info_out(const std::string&);
    void pose_out(const std::string&);
    void set_handdraw_bar(int);
    void set_paint_svg_bar(int);

      protected slots:
    void on_pose_out(const std::string&);
    void on_listen_pose();
    void on_dislisten_pose();
    void on_info_out(const std::string&);
    void on_preview_handdraw();
    void on_opencap();
    void on_opensvg();
    void on_paint_handdraw();
    void on_paint_svg();
    void on_set_handdraw_bar(int);
    void on_set_paint_svg_bar(int);
};
