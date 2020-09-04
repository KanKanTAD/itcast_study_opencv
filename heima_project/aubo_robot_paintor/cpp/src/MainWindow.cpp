#include "MainWindow.h"

#include <qlabel.h>
#include <qobject.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "AuBoDriver.hpp"
#include "AuboRobotMetaType.h"
#include "utils.hpp"

MainWindow::MainWindow(QWidget* ptr) : QWidget(ptr) {
    main_layout.addWidget(new QLabel{"host"}, 0, 0);

    this->ip_edit.setText("192.168.36.25");
    main_layout.addWidget(&this->ip_edit, 0, 1);
    main_layout.addWidget(new QLabel{"port"}, 0, 2);
    this->port_edit.setText("8899");
    main_layout.addWidget(&this->port_edit, 0, 3);

    this->state_label.setText("have no connected");
    main_layout.addWidget(&this->state_label, 1, 2, 1, 2);

    main_layout.addWidget(&this->disconnect_btn, 2, 0);
    main_layout.addWidget(&this->detected_btn, 2, 2);
    main_layout.addWidget(&this->connect_btn, 2, 3);

    main_layout.addWidget(new QLabel{"origin point"}, 3, 0);
    this->origin_edit.setText("-0.19384 ,-0.649,0.00237");
    main_layout.addWidget(&this->origin_edit, 3, 1);

    main_layout.addWidget(new QLabel{"point sample step:"}, 3, 2);
    this->pt_step_edit.setText("10");
    main_layout.addWidget(&this->pt_step_edit, 3, 3);

    main_layout.addWidget(new QLabel{"x axes:"}, 4, 0);
    this->x_axes_edit.setText("-0.3");
    main_layout.addWidget(&this->x_axes_edit, 4, 1);

    main_layout.addWidget(new QLabel{"y axes:"}, 4, 2);
    this->y_axes_edit.setText("-0.2");
    main_layout.addWidget(&this->y_axes_edit, 4, 3);

    main_layout.addWidget(new QLabel{"rx ry rz:"}, 5, 0);
    this->rx_ry_rz.setText("3.14,0,0");
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

    QObject::connect(&this->clean_btn, &QPushButton::clicked, [this]() {
        this->paintor.clear_pts();
    });

    QObject::connect(&this->connect_btn, &QPushButton::clicked, [this]() {
        auto ip   = utils::load_qstring(this->ip_edit.text(), "127.0.0.1");
        auto port = utils::stoi(this->port_edit.text(), 30002);
        std::cout << "connect -> " << ip.toStdString() << ":" << port
                  << std::endl;
        AuBoDriver::get_instance().connect_robot(ip, port);
    });

    QObject::connect(&this->detected_btn, &QPushButton::clicked, [this]() {
        if (AuBoDriver::get_instance().is_connected()) {
            this->state_label.setText("have be connected!");
        } else {
            this->state_label.setText("no connected!");
        }
    });

    QObject::connect(&this->disconnect_btn, &QPushButton::clicked, [this]() {
        std::cout << "disconnect!" << std::endl;
        AuBoDriver::get_instance().disconnect_robot();
    });

    QObject::connect(
        &this->paint_btn, SIGNAL(clicked()), this, SLOT(do_paint()));

    QObject::connect(&this->stop_btn, &QPushButton::clicked, [this]() {
        AuBoDriver::get_instance().stop_all();
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

        AuBoDriver::get_instance().movel_at_once(pose, a, v);
    });

    // AuBoDriver::get_instance().disconnect_callback_func =
    //[this]() mutable -> void {
    // this->state_label.setText("have no connected");
    //};

    // AuBoDriver::get_instance().connect_callback_func =
    //[this]() mutable -> void {
    // this->state_label.setText("robot have be connected!");
    //};

    AuBoDriver::get_instance().way_point_callback_func =
        [this](const aubo_robot_namespace::wayPoint_S& way_pts) -> void {
        for (int i = 0; i < 6; i++) {
            this->pose_labels[i].setText(
                QString::number(AuBoDriver::get_instance().current_pose[i]));
        }
    };

    this->show();
}

void MainWindow::do_paint() {
    std::cout << "do_paint!" << std::endl;

    if (AuBoDriver::get_instance().is_connected() == false) {
        std::cout << "can't paint because of no connnect to robot!"
                  << std::endl;
        return;
    }

    auto epsilon = utils::stod(this->epsilon_edit.text().toStdString(), 0.012);
    AuBoDriver::get_instance().epsilon = epsilon;

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
        std::vector<std::vector<double>>* pts_s = nullptr;
        pts_s = new std::vector<std::vector<double>>{};
        std::cout << pts_s << std::endl;

        for (auto& pts : *muti_pts) {
            for (auto& pt : pts) {
                pts_s->push_back(
                    std::vector<double>{(x_len * pt.x + double_ori->at(0)),
                                        (y_len * pt.y + double_ori->at(1)),
                                        double_ori->at(2),
                                        double_rs->at(0),
                                        double_rs->at(1),
                                        double_rs->at(2)});
            }
            pts_s->push_back(
                std::vector<double>{(x_len * pts.back().x + double_ori->at(0)),
                                    (y_len * pts.back().y + double_ori->at(1)),
                                    double_ori->at(2) * z_coef,
                                    double_rs->at(0),
                                    double_rs->at(1),
                                    double_rs->at(2)});
        }
        std::cout << __FILE__ << "-" << __LINE__
                  << "  pts_s -> size():" << pts_s->size() << std::endl;
        AuBoDriver::get_instance().stop_move_batch();
        AuBoDriver::get_instance().move_batch(MOVETYPE::MOVEL, pts_s, a, v);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void MainWindow::preview() {
    std::cout << "preview!" << std::endl;
    preview_wnd.can_mouse = false;
    preview_wnd.show();
    preview_wnd.setWindowTitle("preview");
    preview_wnd.set_pts_s(
        *(paintor.load_muti_pts(utils::stoi(this->pt_step_edit.text(), 10))));
    preview_wnd.update();
}
