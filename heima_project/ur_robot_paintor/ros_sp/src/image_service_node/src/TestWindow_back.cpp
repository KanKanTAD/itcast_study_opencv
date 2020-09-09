#include "TestWindow.h"

#include <opencv2/core/hal/interface.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>

#include <boost/bind/bind.hpp>
#include <exception>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <thread>

#include "SimpleRobotMoveTask.h"
#include "SimpleSvgToWaysTask.h"
#include "about_svg_utils.hpp"
#include "cv_bridge/cv_bridge.h"
#include "my_robot_move_msgs/PainterMoveActionGoal.h"
#include "my_robot_move_msgs/PainterMoveFeedback.h"
#include "my_robot_move_msgs/PainterMoveGoal.h"
#include "my_robot_move_msgs/Point.h"
#include "my_robot_move_msgs/RobotPoseInfoFeedback.h"
#include "my_robot_move_msgs/RobotPoseInfoGoal.h"
#include "my_robot_move_msgs/SvgToPntss.h"
#include "ros/duration.h"
#include "sensor_msgs/image_encodings.h"

TestWindow::TestWindow() : QWidget(nullptr) {
    qRegisterMetaType<std::string>("std::string");
    _init_virsual();
    _init_event();
    this->show();
}

void TestWindow::_init_virsual() {
    auto main_lyt = new QGridLayout{this};

    int row = 0;

    main_lyt->addWidget(new QLabel{"host:"}, row, 0, Qt::AlignRight);
    host_edit.setText("127.0.0.1");
    main_lyt->addWidget(&host_edit, row, 1, Qt::AlignLeft);
    port_edit.setText("30003");
    main_lyt->addWidget(new QLabel{":"}, row, 2, Qt::AlignCenter);
    main_lyt->addWidget(&port_edit, row, 3, Qt::AlignLeft);

    row++;

    main_lyt->addWidget(&pose_servername_edit, row, 0, 1, 4);

    row++;

    main_lyt->addWidget(&listenpose_btn, row, 0, Qt::AlignRight);
    main_lyt->addWidget(&dislistenpose_btn, row + 1, 0, Qt::AlignRight);
    main_lyt->addWidget(&pose_lab, row, 1, 2, 3);

    row += 2;

    row++;

    main_lyt->addWidget(&opencap_btn, row, 0, Qt::AlignLeft);
    topic_name_edit.setText("camera_image");
    main_lyt->addWidget(&topic_name_edit, row, 1, 1, 2);
    main_lyt->addWidget(&closecap_btn, row, 3, Qt::AlignRight);

    row++;

    main_lyt->addWidget(&opensvg_btn, row, 0, Qt::AlignLeft);
    svgservername_edit.setText("svg_to_ways_server");
    main_lyt->addWidget(&svgservername_edit, row, 1);
    svgfilepath_edit.setText("/home/tad/Picture/svg_s/1.svg");
    main_lyt->addWidget(&svgfilepath_edit, row, 2, 1, 2);

    row++;

    main_lyt->addWidget(&paint_handdraw_btn, row, 0);
    main_lyt->addWidget(&paint_camera_num_btn, row, 1);
    main_lyt->addWidget(&paint_svg_btn, row, 2);
    main_lyt->addWidget(new QLabel{"robot action server name"}, row, 3);

    row++;

    main_lyt->addWidget(&dispaint_handdraw_btn, row, 0);
    main_lyt->addWidget(&dispaint_camera_num_btn, row, 1);
    main_lyt->addWidget(&dispaint_svg_btn, row, 2);
    main_lyt->addWidget(&robot_move_action_server_name_edit, row, 3);

    row++;

    paint_camera_num_bar.setRange(0, 100);
    paint_svg_bar.setRange(0, 100);
    paint_handdraw_bar.setRange(0, 100);

    main_lyt->addWidget(&paint_handdraw_bar, row, 0);
    main_lyt->addWidget(&paint_camera_num_bar, row, 1);
    main_lyt->addWidget(&paint_svg_bar, row, 2);

    row++;

    main_lyt->addWidget(new QLabel{"x_width:"}, row, 0);
    main_lyt->addWidget(&real_width_edit, row, 1);
    main_lyt->addWidget(new QLabel{"y_height:"}, row, 2);
    main_lyt->addWidget(&real_height_edit, row, 3);

    row++;

    main_lyt->addWidget(new QLabel{"ori_xyz:"}, row, 0);
    ori_pose_edit[0].setText("-0.127");
    ori_pose_edit[1].setText("-0.327");
    ori_pose_edit[2].setText("-0.047");
    for (int i = 0; i < 3; i++) {
        main_lyt->addWidget(&this->ori_pose_edit[i], row, 1 + i);
    }

    row++;

    main_lyt->addWidget(new QLabel{"ori_RxRyRz:"}, row, 0);
    ori_pose_edit[3].setText("3.1415");
    ori_pose_edit[4].setText("0");
    ori_pose_edit[5].setText("0");
    for (int i = 3; i < 6; i++) {
        main_lyt->addWidget(&this->ori_pose_edit[i], row, i - 2);
    }

    row++;

    main_lyt->addWidget(new QLabel{"a:"}, row, 0);
    main_lyt->addWidget(&a_edit, row, 1);
    main_lyt->addWidget(new QLabel{"v:"}, row, 2);
    main_lyt->addWidget(&v_edit, row, 3);

    row++;

    main_lyt->addWidget(new QLabel{"epsilon:"}, row, 0);
    main_lyt->addWidget(&epsilon_edit, row, 1);
    main_lyt->addWidget(new QLabel{"tran_z:"}, row, 2);
    main_lyt->addWidget(&tran_z_edit, row, 3);

    row++;

    paintor.setFixedSize(paintor_width, paintor_height);
    main_lyt->addWidget(&paintor, row, 0, 1, 4);
    paintor.show();

    row++;

    main_lyt->addWidget(new QLabel("sample step"), row, 0);
    main_lyt->addWidget(&sample_step_edit, row, 1);
    main_lyt->addWidget(&preview_paintor_btn, row, 2);
    main_lyt->addWidget(&clean_paintor_btn, row, 3);

    row++;

    info_lab.setWordWrap(true);
    main_lyt->addWidget(&info_lab, row, 0, 1, 4);

    row++;
}

void TestWindow::_init_event() {
    QObject::connect(this,
                     SIGNAL(set_paint_svg_bar(int)),
                     this,
                     SLOT(on_set_paint_svg_bar(int)));
    QObject::connect(this,
                     SIGNAL(set_handdraw_bar(int)),
                     this,
                     SLOT(on_set_handdraw_bar(int)));
    QObject::connect(this,
                     SIGNAL(info_out(const std::string&)),
                     this,
                     SLOT(on_info_out(const std::string&)));
    QObject::connect(this,
                     SIGNAL(pose_out(const std::string&)),
                     this,
                     SLOT(on_pose_out(const std::string&)));

    QObject::connect(&opencap_btn, SIGNAL(clicked()), this, SLOT(on_opencap()));

    QObject::connect(&closecap_btn, &QPushButton::clicked, [this]() {
        this->subscriber.shutdown();
        cv::destroyAllWindows();
    });

    QObject::connect(&opensvg_btn, SIGNAL(clicked()), this, SLOT(on_opensvg()));

    QObject::connect(
        &listenpose_btn, SIGNAL(clicked()), this, SLOT(on_listen_pose()));

    QObject::connect(
        &dislistenpose_btn, SIGNAL(clicked()), this, SLOT(on_dislisten_pose()));

    QObject::connect(&clean_paintor_btn, &QPushButton::clicked, [this]() {
        paintor.clear_pts();
    });

    QObject::connect(&preview_paintor_btn,
                     SIGNAL(clicked()),
                     this,
                     SLOT(on_preview_handdraw()));
    QObject::connect(&paint_handdraw_btn,
                     SIGNAL(clicked()),
                     this,
                     SLOT(on_paint_handdraw()));
    QObject::connect(&dispaint_handdraw_btn, &QPushButton::clicked, [this]() {
        emit info_out("dispaint_handdraw_btn clicked!");
        handdraw_task.cancel();
    });

    handdraw_task.tran_callback_func =
        [this](SimpleRobotMoveTask::GoalHandle_t handle) {
            ROS_INFO_STREAM("tran it");
        };
    handdraw_task.feedback_callback_func =
        [this](SimpleRobotMoveTask::GoalHandle_t handle,
               my_robot_move_msgs::PainterMoveFeedbackConstPtr ptr) {
            emit this->set_handdraw_bar(int(ptr->percent * 100));
        };

    QObject::connect(
        &paint_svg_btn, SIGNAL(clicked()), this, SLOT(on_paint_svg()));

    QObject::connect(&dispaint_svg_btn, &QPushButton::clicked, [this]() {
        emit info_out("dispaint_svg_btn clicked!");
        this->move_by_svg_task.cancel();
    });
    handdraw_task.tran_callback_func =
        [this](SimpleRobotMoveTask::GoalHandle_t handle) {
            ROS_INFO_STREAM("tran it");
        };
    handdraw_task.feedback_callback_func =
        [this](SimpleRobotMoveTask::GoalHandle_t handle,
               my_robot_move_msgs::PainterMoveFeedbackConstPtr ptr) {
            emit this->set_handdraw_bar(int(ptr->percent * 100));
        };

    opensvg_task.on_successed_func = [](SimpleSvgToWaysTask::Bean_t& bean) {
        auto& obj = bean;
        cv::Mat pic =
            cv::Mat::zeros(obj.request.height, obj.request.width, CV_8UC1);
        auto& pts = obj.response.pts.data;
        for (int i = 1; i < pts.size(); i++) {
            cv::Scalar color = pts[i].z == pts[i - 1].z
                                   ? cv::Scalar::all(255.0)
                                   : cv::Scalar::all(128.0);
            cv::line(pic,
                     {int(pts[i - 1].x), int(pts[i - 1].y)},
                     {int(pts[i].x), int(pts[i].y)},
                     color);
        }
        cv::imshow("pic", pic);
    };
    opensvg_task.on_fail_func = [this](int code) {
        if (-1 == code) {
            emit this->info_out("server timeout");
        } else if (-2 == code) {
            emit this->info_out("file open error!");
        }
    };
    paint_svg_task.on_fail_func = [this](int code) {
        if (-1 == code) {
            emit this->info_out("server timeout");
        } else if (-2 == code) {
            emit this->info_out("file open error!");
        }
    };
    paint_svg_task.on_successed_func =
        [this](SimpleSvgToWaysTask::Bean_t& obj) {
            auto _server_name =
                loadQString(this->robot_move_action_server_name_edit,
                            "ur_move_driver_server")
                    .toStdString();
            move_by_svg_task.server_name = _server_name;
            my_robot_move_msgs::PainterMoveGoal goal;
            this->get_half_info(goal);
            goal.ways = obj.response.pts;
            auto code = move_by_svg_task.send_goal(goal);
            switch (code) {
                case -1:
                    emit info_out("nullptr node");
                    break;
                case 1:
                    emit info_out(_server_name + " timeout !");
                    break;
                default:
                    break;
            }
        };
}

void TestWindow::simple_cap_test_callback(
    const sensor_msgs::ImageConstPtr& ptr) {
    auto im = cv_bridge::toCvCopy(*ptr, sensor_msgs::image_encodings::BGR8);
    cv::imshow("info", im->image);
}

void TestWindow::on_opencap() {
    if (nullptr == node) {
        emit info_out("node is nullptr!");
        return;
    }
    subscriber.shutdown();

    auto topic_name =
        loadQString(topic_name_edit, "camera_image").toStdString();

    subscriber = node->subscribe<sensor_msgs::Image>(
        topic_name, 1024, TestWindow::simple_cap_test_callback);
    emit info_out("subscribe to '" + subscriber.getTopic() + "'");
}

void TestWindow::on_info_out(const std::string& str) {
    info_lab.setText(QString::fromStdString(str));
}
void TestWindow::on_pose_out(const std::string& str) {
    pose_lab.setText(QString::fromStdString(str));
}

void TestWindow::on_opensvg() {
    emit info_out("on opensvg");
    auto _server_name =
        loadQString(svgservername_edit, "svg_to_ways_server").toStdString();
    auto file_path =
        loadQString(svgfilepath_edit, "/home/tad/Picture/svg_s/8.svg")
            .toStdString();
    SimpleSvgToWaysTask::Bean_t bean;
    SimpleSvgToWaysTask::_set_bean_pathd_by_filename1(bean, file_path);
    SimpleSvgToWaysTask::_set_default_request_bean(bean);
    this->opensvg_task.call(_server_name, bean);
}

void TestWindow::on_listen_pose() {
    emit info_out("on listen pose");
    if (nullptr == node) {
        emit info_out("node is nullptr");
        return;
    }
    new std::thread([this]() {
        auto name = loadQString(pose_servername_edit, "ur_robot_pose_server")
                        .toStdString();
        pose_client.reset(new _ActionClient_t(*node, name));
        emit info_out("action to '" + name + "'");
        if (!pose_client->waitForActionServerToStart(ros::Duration(5))) {
            emit info_out("server '" + name + "' timeout 5 seconds");
            return;
        }
        is_cancel_listen = false;

        my_robot_move_msgs::RobotPoseInfoGoal goal;
        goal.host = loadQString(host_edit, "127.0.0.1").toStdString();
        goal.port = loadQString(port_edit, "30003").toInt();
        emit info_out("sendgoal -- " + goal.host + ":" +
                      std::to_string(goal.port));
        goal_handle = pose_client->sendGoal(
            goal,
            [](GoalHandle_t handle) { ROS_INFO_STREAM("tran it!"); },
            // boost::bind(
            //&TestWindow::on_tran_callback, this, boost::placeholders::_1),
            boost::bind(&TestWindow::on_feedback_callback,
                        this,
                        boost::placeholders::_1,
                        boost::placeholders::_2));
    });
}

void TestWindow::on_dislisten_pose() {
    goal_handle.cancel();
}

void TestWindow::on_tran_callback(GoalHandle_t handle) {
    ROS_INFO_STREAM("tran it");
}

void TestWindow::on_feedback_callback(
    GoalHandle_t handle,
    my_robot_move_msgs::RobotPoseInfoFeedbackConstPtr ptr) {
    auto& p = ptr->pose;
    char buff[1024];
    std::sprintf(buff,
                 "%3.6f ,%3.6f ,%3.6f \n%3.6f ,%3.6f ,%3.6f ",
                 p.x,
                 p.y,
                 p.z,
                 p.rx,
                 p.ry,
                 p.rz);
    emit pose_out(buff);
}

void TestWindow::on_preview_handdraw() {
    auto step   = loadQString(sample_step_edit, "10").toInt();
    auto ptss   = paintor.load_muti_pts(step);
    cv::Mat pic = cv::Mat::zeros(paintor_height, paintor_width, CV_8UC1);

    for (auto& pts : *ptss) {
        for (int i = 1; i < pts.size(); i++) {
            cv::line(pic,
                     cv::Point2i{pts.at(i - 1).int_x(), pts.at(i - 1).int_y()},
                     cv::Point2i{pts.at(i).int_x(), pts.at(i).int_y()},
                     cv::Scalar::all(255.0));
        }
    }

    cv::imshow("preview", pic);
}

void TestWindow::get_half_info(my_robot_move_msgs::PainterMoveGoal& goal) {
    goal.acceleration = loadQString(this->a_edit, "0.14").toFloat();
    goal.velocity     = loadQString(this->v_edit, "0.25").toFloat();
    goal.epsilon      = loadQString(this->epsilon_edit, "0.0128").toFloat();
    goal.host         = loadQString(this->host_edit, "127.0.0.1").toStdString();
    goal.port         = loadQString(this->port_edit, "30003").toInt();
}

void TestWindow::get_ori_pose(my_robot_move_msgs::Point& pose) {
    pose.x  = loadQString(this->ori_pose_edit[0], "0.0").toFloat();
    pose.y  = loadQString(this->ori_pose_edit[1], "0.0").toFloat();
    pose.z  = loadQString(this->ori_pose_edit[2], "0.0").toFloat();
    pose.rx = loadQString(this->ori_pose_edit[3], "0.0").toFloat();
    pose.ry = loadQString(this->ori_pose_edit[4], "0.0").toFloat();
    pose.rz = loadQString(this->ori_pose_edit[5], "0.0").toFloat();
}

void TestWindow::set_handdraw_goal(my_robot_move_msgs::PainterMoveGoal& goal) {
    auto width  = loadQString(real_width_edit, "-0.4").toDouble();
    auto height = loadQString(real_height_edit, "0.2").toDouble();
    auto tran_z = loadQString(tran_z_edit, "0.0").toFloat();
    auto step   = loadQString(sample_step_edit, "10").toInt();
    auto ptss   = paintor.load_muti_pts(step);
    get_half_info(goal);
    my_robot_move_msgs::Point pose;
    get_ori_pose(pose);
    if (tran_z == 0.0f) {
        tran_z = pose.z * 1.5;
    }
    my_robot_move_msgs::Point p;
    p          = pose;
    auto& ways = goal.ways.data;
    for (auto& pts : *ptss) {
        for (auto& pt : pts) {
            p.x = pt.x / paintor_width * width + pose.x;
            p.y = pt.y / paintor_height * height + pose.y;
            p.z = pose.z;
            ways.push_back(p);
        }
        p.z = tran_z;
        ways.push_back(p);
    }
    p   = pose;
    p.z = tran_z;
    ways.push_back(p);
}
void TestWindow::on_paint_handdraw() {
    ROS_INFO_STREAM("on paint handdraw");
    emit this->set_handdraw_bar(0);

    new std::thread([this]() {
        auto server_name = loadQString(robot_move_action_server_name_edit,
                                       "ur_move_driver_server")
                               .toStdString();
        handdraw_task.server_name = server_name;
        my_robot_move_msgs::PainterMoveGoal goal;
        set_handdraw_goal(goal);
        auto code = handdraw_task.send_goal(goal);
        switch (code) {
            case -1:
                emit info_out("nullptr node");
                break;
            case 1:
                emit info_out("timeout !");
                break;
            default:
                break;
        }
    });
}

void TestWindow::on_set_handdraw_bar(int v) {
    this->paint_handdraw_bar.setValue(v);
}
void TestWindow::on_set_paint_svg_bar(int v) {
    this->paint_svg_bar.setValue(v);
}

void TestWindow::on_paint_svg() {
    ROS_INFO_STREAM("on paint svg");
    emit this->set_paint_svg_bar(0);
    emit info_out("on paint svg");

    auto _server_name =
        loadQString(svgservername_edit, "svg_to_ways_server").toStdString();
    auto file_path =
        loadQString(svgfilepath_edit, "/home/tad/Picture/svg_s/8.svg")
            .toStdString();

    SimpleSvgToWaysTask::Bean_t obj;
    SimpleSvgToWaysTask::_set_bean_pathd_by_filename0(obj, file_path);
    /* set coef_ */
    {
        my_robot_move_msgs::Point pose;
        this->get_ori_pose(pose);
        auto tran_z        = loadQString(tran_z_edit, "0").toFloat();
        tran_z             = tran_z == 0.0f ? pose.z * 1.5f : tran_z;
        auto width         = loadQString(real_width_edit, "-0.4").toFloat();
        auto height        = loadQString(real_height_edit, "0.2").toFloat();
        obj.request.ori_x  = pose.x;
        obj.request.ori_y  = pose.y;
        obj.request.ori_z  = pose.z;
        obj.request.rx     = pose.rx;
        obj.request.ry     = pose.ry;
        obj.request.rz     = pose.rz;
        obj.request.tran_z = tran_z;
        obj.request.width  = width;
        obj.request.height = height;
    } /* end set*/

    this->opensvg_task.call(_server_name, obj);
}
