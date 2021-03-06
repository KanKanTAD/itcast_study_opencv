#include "MainWindow.h"

#include <qlabel.h>
#include <qobject.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "URDriver.hpp"
#include "about_svg_utils.hpp"
#include "src/Paintor.h"
#include "utils.hpp"

MainWindow::MainWindow(QWidget* ptr) : QWidget(ptr) {
    main_layout.addWidget(new QLabel{"host"}, 0, 0);

    this->ip_edit.setText("192.168.36.26");
    main_layout.addWidget(&this->ip_edit, 0, 1);
    main_layout.addWidget(new QLabel{"port"}, 0, 2);
    this->port_edit.setText("30003");
    main_layout.addWidget(&this->port_edit, 0, 3);

    this->state_label.setText("have no connected");
    main_layout.addWidget(&this->state_label, 1, 2, 1, 2);

    main_layout.addWidget(&this->disconnect_btn, 2, 0);

    main_layout.addWidget(&this->connect_btn, 2, 3);

    main_layout.addWidget(new QLabel{"origin point"}, 3, 0);
    this->origin_edit.setText("-0.128 ,-0.415,0.042");
    main_layout.addWidget(&this->origin_edit, 3, 1);

    main_layout.addWidget(new QLabel{"point sample step:"}, 3, 2);
    this->pt_step_edit.setText("10");
    main_layout.addWidget(&this->pt_step_edit, 3, 3);

    main_layout.addWidget(new QLabel{"x axes:"}, 4, 0);
    this->x_axes_edit.setText("0.4");
    main_layout.addWidget(&this->x_axes_edit, 4, 1);

    main_layout.addWidget(new QLabel{"y axes:"}, 4, 2);
    this->y_axes_edit.setText("0.2");
    main_layout.addWidget(&this->y_axes_edit, 4, 3);

    main_layout.addWidget(new QLabel{"rx ry rz:"}, 5, 0);
    this->rx_ry_rz.setText("2.6,1.18,-0.68");
    main_layout.addWidget(&this->rx_ry_rz, 5, 1, 1, 3);

    this->paintor.setFixedSize(paintor_width, paintor_height);
    main_layout.addWidget(&this->paintor, 6, 0, 1, 4);

    main_layout.addWidget(&this->clean_btn, 7, 0);
    main_layout.addWidget(&this->stop_btn, 7, 1);
    main_layout.addWidget(&this->preview_btn, 7, 2);
    main_layout.addWidget(&this->paint_btn, 7, 3);

    const char* names[6] = {"x:", "y:", "z:", "rx:", "ry:", "rz:"};
    for (int i = 0; i < 6; ++i) {
        main_layout.addWidget(new QLabel{names[i]}, 8 + i, 0);
        main_layout.addWidget(&(this->pose_edits[i]), 8 + i, 1);
        main_layout.addWidget(&(this->pose_labels[i]), 8 + i, 2);
    }

    main_layout.addWidget(new QLabel{"a:"}, 8 + 6, 0);
    this->a_edit.setText("0.12");
    main_layout.addWidget(&this->a_edit, 8 + 6, 1);

    main_layout.addWidget(new QLabel{"z coef:"}, 8 + 6, 2);
    this->coef_z_edit.setText("1.5");
    main_layout.addWidget(&this->coef_z_edit, 8 + 6, 3);

    main_layout.addWidget(new QLabel{"v:"}, 9 + 6, 0);
    this->v_edit.setText("0.25");
    main_layout.addWidget(&this->v_edit, 9 + 6, 1);

    main_layout.addWidget(new QLabel{"epsilon"}, 10 + 6, 0);
    this->epsilon_edit.setText("0.018");
    main_layout.addWidget(&this->epsilon_edit, 10 + 6, 1);

    main_layout.addWidget(&this->test_movel_btn, 17, 0, 1, 4);

    main_layout.addWidget(&this->filepath_edit, 18, 0, 1, 3);
    main_layout.addWidget(&this->paint_svg_btn, 18, 3);

    QObject::connect(&this->clean_btn, &QPushButton::clicked, [this]() {
        this->paintor.clear_pts();
    });

    QObject::connect(&this->connect_btn, &QPushButton::clicked, [this]() {
        auto ip   = utils::load_qstring(this->ip_edit.text(), "127.0.0.1");
        auto port = utils::stoi(this->port_edit.text(), 30002);
        std::cout << "connect -> " << ip.toStdString() << ":" << port
                  << std::endl;
        URDriver::get_instance().connect_robot(ip, port);
    });

    QObject::connect(&this->disconnect_btn, &QPushButton::clicked, [this]() {
        std::cout << "disconnect!" << std::endl;
        URDriver::get_instance().disconnect_robot();
    });

    QObject::connect(
        &this->paint_btn, SIGNAL(clicked()), this, SLOT(do_paint()));

    QObject::connect(&this->stop_btn, &QPushButton::clicked, [this]() {
        URDriver::get_instance().stop_all();
    });

    QObject::connect(
        &this->preview_btn, SIGNAL(clicked()), this, SLOT(preview()));
    QObject::connect(&this->test_movel_btn, &QPushButton::clicked, [this]() {
        std::cout << "do test_movel_btn" << std::endl;
        auto a = utils::stod(this->a_edit.text().toStdString(), 0.012);
        auto v = utils::stod(this->v_edit.text().toStdString(), 0.025);
        std::cout << "a:" << a << " --- "
                  << "v:" << v << std::endl;
        std::vector<double> pose;
        for (int i = 0; i < 6; ++i) {
            pose.push_back(utils::stod(pose_edits[i].text().toStdString()));
        }

        URDriver::get_instance().movel_at_once(pose, a, v);
    });

    QObject::connect(&this->paint_svg_btn, &QPushButton::clicked, [this]() {
        auto filepath = utils::load_qstring(
            this->filepath_edit.text(),
            "/home/tad/Public/itcast_study_opencv/heima_project/robot_paintor/"
            "cpp/paint_svg/svg_res/zh.svg");
        auto ways = utils::get_ways_form_svg(filepath.toStdString());
        utils::_normalize(*ways);
        utils::_extendto(*ways, this->paintor_width, this->paintor_height);
        std::vector<std::vector<point2d_t>> mpts;
        for (auto& way : *ways) {
            mpts.push_back(std::vector<point2d_t>{});
            for (auto& pt : way) {
                mpts.back().push_back({utils::round(pt.x), utils::round(pt.y)});
            }
        }
        this->paintor.set_pts(mpts);
    });

    URDriver::get_instance().disconnect_callback_func =
        [this]() mutable -> void {
        this->state_label.setText("have no connected");
    };

    URDriver::get_instance().connect_callback_func = [this]() mutable -> void {
        this->state_label.setText("robot have be connected!");
    };

    URDriver::get_instance().readyread_callback_func =
        [this](URData& ur_data) -> void {
        char buf[1024];
        for (int i = 0; i < 6; ++i) {
            // memset(buf, 0, 1024);
            // sprintf(buf, "%.6f", ur_data.Tool_vector_actual[i]);
            // this->pose_labels[i].setText(buf);
            // this->pose_labels[i].setText(QString::fromStdString(
            // std::to_string(ur_data.Tool_vector_actual[i])));
            this->pose_labels[i].setText(
                QString::number(ur_data.Tool_vector_actual[i]));
        }
    };
    this->show();
}

void MainWindow::do_paint() {
    std::cout << "do_paint!" << std::endl;

    if (URDriver::get_instance().is_connected() == false) {
        std::cout << "can't paint because of no connnect to robot!"
                  << std::endl;
        return;
    }

    auto epsilon = utils::stod(this->epsilon_edit.text().toStdString(), 0.012);
    URDriver::get_instance().epsilon = epsilon;

    auto r_str     = utils::load_qstring(this->rx_ry_rz.text(), "0,0,0");
    auto rs        = utils::split(r_str.toStdString());
    auto double_rs = utils::strs2doubles(*rs);
    std::cout << "rx:" << double_rs->at(0) << " ,ry:" << double_rs->at(1)
              << " rz:" << double_rs->at(2) << std::endl;

    auto double_ori = utils::strs2doubles(*utils::split(
        utils::load_qstring(this->origin_edit.text(), "0,0,0").toStdString()));
    std::cout << "ox:" << double_ori->at(0) << " ,oy:" << double_ori->at(1)
              << " ,oz:" << double_ori->at(2) << std::endl;

    auto x_len = utils::stod(this->x_axes_edit.text().toStdString(), -100);
    auto y_len = utils::stod(this->y_axes_edit.text().toStdString(), -100);
    std::cout << "x_len:" << x_len << " ,y_len:" << y_len << std::endl;

    auto a = utils::stod(this->a_edit.text().toStdString(), 0.12);
    auto v = utils::stod(this->v_edit.text().toStdString(), 0.25);

    int pt_step = utils::stoi(this->pt_step_edit.text(), 10);

    auto z_coef = utils::stod(this->coef_z_edit.text().toStdString(), 1.3);

    auto muti_pts = this->paintor.load_muti_pts(pt_step);

    for (auto& pts : *muti_pts) {
        point2d_t::normalize(pts, {0, 0}, {paintor_width, paintor_height});
        // std::cout << pts.back().str() << std::endl;
    }

    try {
        for (auto& pts : *muti_pts) {
            for (auto& pt : pts) {
                double ps[6] = {(x_len * pt.x + double_ori->at(0)),
                                (y_len * pt.y + double_ori->at(1)),
                                double_ori->at(2),
                                double_rs->at(0),
                                double_rs->at(1),
                                double_rs->at(2)};
                URDriver::get_instance().movel(ps, a, v);
            }
            double t[6] = {(x_len * pts.back().x + double_ori->at(0)),
                           (y_len * pts.back().y + double_ori->at(1)),
                           double_ori->at(2) * z_coef,
                           double_rs->at(0),
                           double_rs->at(1),
                           double_rs->at(2)};
            URDriver::get_instance().movel(t, a, v);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void MainWindow::preview() {
    new std::thread([this]() {
        cv::Mat mt{
            cv::Mat::zeros(this->paintor_height, this->paintor_width, CV_8UC1)};

        auto muti_pts =
            paintor.load_muti_pts(utils::stoi(this->pt_step_edit.text()));
        for (auto& pts : *muti_pts) {
            for (int i = 1; i < pts.size(); ++i) {
                cv::line(mt,
                         {pts[i - 1].int_x(), pts[i - 1].int_y()},
                         {pts[i].int_x(), pts[i].int_y()},
                         cv::Scalar::all(255.0));
            }
        }
        cv::imshow("info", mt);
        // std::cout << "out preview" << std::endl;
    });
}
