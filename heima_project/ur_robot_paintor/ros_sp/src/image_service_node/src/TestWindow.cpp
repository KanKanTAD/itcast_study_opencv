#include "TestWindow.h"

#include <string>

#include "SimpleRobotInfoTask.h"
#include "SimpleRobotMoveTask.h"
#include "my_robot_move_msgs/RobotPoseInfoFeedback.h"

TestWindow::TestWindow() : QWidget(nullptr) {
    qRegisterMetaType<std::string>("std::string");
    _init_virsual();
    _init_event();
    this->show();
}
void TestWindow::set_node(ros::NodeHandle& node) {
    this->node                 = &node;
    this->robot_pose_task.node = &node;
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
    ori_pose_edit[2].setText("0.047");
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
    tran_z_edit.setText("0.08");
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
                     SIGNAL(info_out(const std::string&)),
                     this,
                     SLOT(on_info_out(const std::string&)));
    QObject::connect(this,
                     SIGNAL(pose_out(const std::string&)),
                     this,
                     SLOT(on_pose_out(const std::string&)));
    QObject::connect(
        &listenpose_btn, SIGNAL(clicked()), this, SLOT(on_listen_pose()));

    QObject::connect(
        &dislistenpose_btn, SIGNAL(clicked()), this, SLOT(on_dislisten_pose()));
    QObject::connect(&preview_paintor_btn,
                     SIGNAL(clicked()),
                     this,
                     SLOT(on_preview_handdraw()));
    QObject::connect(&clean_paintor_btn, &QPushButton::clicked, [this]() {
        paintor.clear_pts();
    });
    QObject::connect(&opencap_btn, SIGNAL(clicked()), this, SLOT(on_opencap()));
    QObject::connect(&closecap_btn, &QPushButton::clicked, [this]() {
        camera_task.cancel();
    });

    robot_pose_task.on_feedback_callback_func =
        [this](SimpleRobotInfoTask::GoalHandle_t handle,
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
        };
    _init_about_svg_event();
    _init_about_handdraw_event();
    _init_about_paint_svg_event();
}

void TestWindow::on_listen_pose() {
    emit info_out("on listen pose");
    robot_pose_task.node = this->node;
    auto name =
        loadQString(pose_servername_edit, "ur_robot_pose_server").toStdString();
    robot_pose_task.server_name = name;
    my_robot_move_msgs::RobotPoseInfoGoal goal;
    goal.host = loadQString(host_edit, "127.0.0.1").toStdString();
    goal.port = loadQString(port_edit, "30003").toInt();
    auto code = robot_pose_task.run_goal(goal);
    if (-1 == code) {
        emit info_out("node is nullptr");
        return;
    } else if (-2 == code) {
        emit info_out("server '" + name + "' timeout 5 seconds");
        return;
    }
}

void TestWindow::on_dislisten_pose() {
    robot_pose_task.cancel();
}

void TestWindow::on_info_out(const std::string& str) {
    info_lab.setText(QString::fromStdString(str));
}
void TestWindow::on_pose_out(const std::string& str) {
    pose_lab.setText(QString::fromStdString(str));
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

void TestWindow::on_opencap() {
    if (nullptr == node) {
        emit info_out("node is nullptr!");
        return;
    }

    auto topic_name =
        loadQString(topic_name_edit, "camera_image").toStdString();
    camera_task.node        = this->node;
    camera_task.server_name = topic_name;
    camera_task.run_goal();
    emit info_out("subscribe to '" + topic_name + "'");
}
void TestWindow::_init_about_svg_event() {
    QObject::connect(&opensvg_btn, SIGNAL(clicked()), this, SLOT(on_opensvg()));
    svg_to_ways_task.on_successed_func = [](SimpleSvgToWaysTask::Bean_t& bean) {
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
    svg_to_ways_task.on_fail_func = [this](int code) {
        if (-1 == code) {
            emit this->info_out("server timeout");
        } else if (-2 == code) {
            emit this->info_out("file open error!");
        }
    };
}
void TestWindow::on_opensvg() {
    emit info_out("on opensvg");
    auto _server_name =
        loadQString(svgservername_edit, "svg_to_ways_server").toStdString();
    auto file_path =
        loadQString(svgfilepath_edit, "/home/tad/Picture/svg_s/8.svg")
            .toStdString();
    svg_to_ways_task.node        = this->node;
    svg_to_ways_task.server_name = _server_name;
    SimpleSvgToWaysTask::Bean_t bean;
    SimpleSvgToWaysTask::_set_bean_pathd_by_filename1(bean, file_path);
    SimpleSvgToWaysTask::_set_default_request_bean(bean);
    this->svg_to_ways_task.run_goal(bean);
}

void TestWindow::_init_about_handdraw_event() {
    QObject::connect(this,
                     SIGNAL(set_handdraw_bar(int)),
                     this,
                     SLOT(on_set_handdraw_bar(int)));
    QObject::connect(&paint_handdraw_btn,
                     SIGNAL(clicked()),
                     this,
                     SLOT(on_paint_handdraw()));
    QObject::connect(&dispaint_handdraw_btn, &QPushButton::clicked, [this]() {
        emit info_out("dispaint_handdraw_btn clicked!");
        this->hanndraw_task.cancel();
    });
    hanndraw_task.feedback_callback_func =
        [this](SimpleRobotMoveTask::GoalHandle_t handle,
               my_robot_move_msgs::PainterMoveFeedbackConstPtr ptr) mutable {
            emit this->set_handdraw_bar(int(ptr->percent));
        };
}

void TestWindow::on_paint_handdraw() {
    ROS_INFO_STREAM("on paint handdraw");
    emit this->info_out("on paint handdraw");
    emit this->set_handdraw_bar(0);

    new std::thread([this]() {
        auto server_name = loadQString(robot_move_action_server_name_edit,
                                       "ur_move_driver_server")
                               .toStdString();
        hanndraw_task.node        = this->node;
        hanndraw_task.server_name = server_name;
        my_robot_move_msgs::PainterMoveGoal goal;
        this->set_handdraw_goal(goal);
        auto code = this->hanndraw_task.run_goal(goal);
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
    auto tran_z = loadQString(tran_z_edit, "0.1").toFloat();
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
void TestWindow::_init_about_paint_svg_event() {
    QObject::connect(this,
                     SIGNAL(set_paint_svg_bar(int)),
                     this,
                     SLOT(on_set_paint_svg_bar(int)));
    QObject::connect(
        &paint_svg_btn, SIGNAL(clicked()), this, SLOT(on_paint_svg()));

    QObject::connect(&dispaint_svg_btn, &QPushButton::clicked, [this]() {
        emit info_out("dispaint_svg_btn clicked!");
        this->svg_paint_task.cancel();
    });
    svg_paint_task.feedback_callback_func =
        [this](SimpleRobotMoveTask::GoalHandle_t handle,
               my_robot_move_msgs::PainterMoveFeedbackConstPtr ptr) mutable {
            emit this->set_paint_svg_bar(int(ptr->percent));
        };
    svg_to_ways_paint_task.on_successed_func =
        [this](SimpleSvgToWaysTask::Bean_t& obj) mutable {
            ROS_INFO_STREAM("successed get ways ,painting...");
            emit info_out("successed get ways ,painting...");
            this->svg_paint_task.server_name =
                loadQString(this->robot_move_action_server_name_edit,
                            "ur_move_driver_server")
                    .toStdString();
            this->svg_paint_task.node = this->node;
            my_robot_move_msgs::PainterMoveGoal goal;
            get_half_info(goal);
            goal.ways.data.swap(obj.response.pts.data);
            ROS_INFO_STREAM("run_goal to painting... to -->" + goal.host + ":" +
                            std::to_string(goal.port));
            emit info_out("run_goal to painting... to -->" + goal.host + ":" +
                          std::to_string(goal.port));
            this->svg_paint_task.run_goal(goal);
        };
    svg_to_ways_paint_task.on_fail_func = [this](int code) {
        if (-1 == code) {
            emit this->info_out("server timeout");
        } else if (-2 == code) {
            emit this->info_out("file open error!");
        }
    };
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
    svg_to_ways_paint_task.node        = this->node;
    svg_to_ways_paint_task.server_name = _server_name;
    SimpleSvgToWaysTask::Bean_t obj;
    SimpleSvgToWaysTask::_set_bean_pathd_by_filename0(obj, file_path);
    obj.request.width  = loadQString(real_width_edit, "-0.4").toDouble();
    obj.request.height = loadQString(real_height_edit, "0.2").toDouble();
    obj.request.ori_x = loadQString(this->ori_pose_edit[0], "-0.17").toDouble();
    obj.request.ori_y =
        loadQString(this->ori_pose_edit[1], "-0.413").toDouble();
    obj.request.ori_z = loadQString(this->ori_pose_edit[2], "0.041").toDouble();
    obj.request.rx = loadQString(this->ori_pose_edit[3], "3.1415").toDouble();
    obj.request.ry = loadQString(this->ori_pose_edit[4], "0").toDouble();
    obj.request.rz = loadQString(this->ori_pose_edit[5], "0").toDouble();
    obj.request.tran_z = loadQString(this->tran_z_edit, "0.1").toDouble();
    ROS_INFO_STREAM("run goal!!!");
    this->svg_to_ways_paint_task.run_goal(obj);
}
