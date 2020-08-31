#include "MainWindow.h"

#include <qobject.h>

#include <iostream>
#include <string>

#include "URDriver.hpp"
#include "utils.hpp"

MainWindow::MainWindow(QWidget* ptr) : QWidget(ptr) {
    main_layout.addWidget(new QLabel{"host"}, 0, 0);

    this->ip_edit.setText("192.168.36.26");
    main_layout.addWidget(&this->ip_edit, 0, 1);
    main_layout.addWidget(new QLabel{"port"}, 0, 2);
    this->port_edit.setText("30002");
    main_layout.addWidget(&this->port_edit, 0, 3);

    this->state_label.setText("have no connected");
    main_layout.addWidget(&this->state_label, 1, 2, 1, 2);

    main_layout.addWidget(&this->disconnect_btn, 2, 0);

    main_layout.addWidget(&this->connect_btn, 2, 3);

    main_layout.addWidget(new QLabel{"origin point"}, 3, 0);
    main_layout.addWidget(&this->origin_edit, 3, 1);
    main_layout.addWidget(new QLabel{"x axes:"}, 4, 0);
    this->x_axes_edit.setText("3");
    main_layout.addWidget(&this->x_axes_edit, 4, 1);

    main_layout.addWidget(new QLabel{"y axes:"}, 4, 2);
    this->y_axes_edit.setText("3");
    main_layout.addWidget(&this->y_axes_edit, 4, 3);

    main_layout.addWidget(new QLabel{"rx ry rz:"}, 5, 0);
    main_layout.addWidget(&this->rx_ry_rz, 5, 1, 1, 3);

    this->paintor.setFixedSize(paintor_width, paintor_height);
    main_layout.addWidget(&this->paintor, 6, 0, 1, 4);

    main_layout.addWidget(&this->clean_btn, 7, 0);
    main_layout.addWidget(&this->stop_btn, 7, 1, 1, 2);
    main_layout.addWidget(&this->paint_btn, 7, 3);

    const char* names[6] = {"x:", "y:", "z:", "rx:", "ry:", "rz:"};
    for (int i = 0; i < 6; ++i) {
        main_layout.addWidget(new QLabel{names[i]}, 8 + i, 0);
        main_layout.addWidget(&(this->pose_edits[i]), 8 + i, 1);
    }

    main_layout.addWidget(new QLabel{"a:"}, 8, 2);
    this->a_edit.setText("1.2");
    main_layout.addWidget(&this->a_edit, 8, 3);

    main_layout.addWidget(new QLabel{"v:"}, 9, 2);
    this->v_edit.setText("0.25");
    main_layout.addWidget(&this->v_edit, 9, 3);

    main_layout.addWidget(&this->test_movel_btn, 8 + 6, 0, 1, 4);

    QObject::connect(&this->clean_btn, &QPushButton::clicked, [this]() {
        this->paintor.clear_pts();
    });

    URDriver::get_instance().connect_callback_func = [this]() mutable -> void {
        this->state_label.setText("robot have be connected!");
    };
    QObject::connect(&this->connect_btn, &QPushButton::clicked, [this]() {
        auto ip   = utils::load_qstring(this->ip_edit.text(), "127.0.0.1");
        auto port = utils::stoi(this->port_edit.text(), 30002);
        std::cout << "connect -> " << ip.toStdString() << ":" << port
                  << std::endl;
        URDriver::get_instance().connect_robot(ip, port);
    });

    URDriver::get_instance().disconnect_callback_func =
        [this]() mutable -> void {
        this->state_label.setText("have no connected");
    };

    QObject::connect(&this->disconnect_btn, &QPushButton::clicked, [this]() {
        std::cout << "disconnect!" << std::endl;
        URDriver::get_instance().disconnect_robot();
    });

    QObject::connect(
        &this->paint_btn, SIGNAL(clicked()), this, SLOT(do_paint()));

    QObject::connect(&this->stop_btn, &QPushButton::clicked, [this]() {
        URDriver::get_instance().stop_all();
    });
    QObject::connect(&this->test_movel_btn, &QPushButton::clicked, [this]() {
        std::cout << "do test_movel_btn" << std::endl;
        // auto a = utils::stod(this->a_edit.text().toStdString(), 1.2);
        // auto v = utils::stod(this->v_edit.text().toStdString(), 0.25);
        auto a = std::stod(this->a_edit.text().toStdString());
        auto v = std::stod(this->v_edit.text().toStdString());
        std::cout << "a:" << a << " --- "
                  << "v:" << v << std::endl;
        std::vector<double> pose;
        for (int i = 0; i < 6; ++i) {
            pose.push_back(std::stod(pose_edits[i].text().toStdString()));
        }

        URDriver::get_instance().movel_at_once(pose, a, v);
    });

    this->show();
}

void MainWindow::do_paint() {
    std::cout << "do_paint!" << std::endl;

    if (URDriver::get_instance().is_connected() == false) {
        std::cout << "can't paint because of no connnect to robot!"
                  << std::endl;
        return;
    }

    auto muti_pts = this->paintor.load_muti_pts(10);
    for (auto& pts : *muti_pts) {
        point2d_t::normalize(pts, {0, 0}, {paintor_width, paintor_height});
    }

    auto r_str     = utils::load_qstring(this->rx_ry_rz.text(), "0,0,0");
    auto rs        = utils::split(r_str.toStdString());
    auto double_rs = utils::strs2doubles(*rs);

    auto double_ori = utils::strs2doubles(*utils::split(
        utils::load_qstring(this->origin_edit.text(), "0,0,0").toStdString()));

    auto x_len = utils::stod(this->x_axes_edit.text().toStdString(), 1);
    auto y_len = utils::stod(this->y_axes_edit.text().toStdString(), 1);

    auto a = std::stod(this->a_edit.text().toStdString());
    auto v = std::stod(this->v_edit.text().toStdString());
    std::cout << "a:" << a << " --- "
              << "v:" << v << std::endl;

    try {
        for (auto& pts : *muti_pts) {
            for (auto& pt : pts) {
                double ps[6] = {x_len * (pt.x + double_ori->at(0)),
                                y_len * (pt.y + double_ori->at(1)),
                                double_ori->at(2),
                                double_rs->at(0),
                                double_rs->at(1),
                                double_rs->at(2)};
                URDriver::get_instance().movel(ps, a, v);
            }
            double t[6] = {x_len * (pts.back().x + double_ori->at(0)),
                           y_len * (pts.back().y + double_ori->at(1)),
                           double_ori->at(2),
                           double_rs->at(0),
                           double_rs->at(1),
                           double_rs->at(2)};
            URDriver::get_instance().movel(t, a, v);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
