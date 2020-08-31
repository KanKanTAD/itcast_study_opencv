#include "MainWindow.h"

#include <qobject.h>

#include <iostream>

#include "URDriver.hpp"
#include "utils.hpp"

MainWindow::MainWindow(QWidget* ptr) : QWidget(ptr) {
    main_layout.addWidget(new QLabel{"host"}, 0, 0);
    main_layout.addWidget(&this->ip_edit, 0, 1);
    main_layout.addWidget(new QLabel{"port"}, 0, 2);
    this->port_edit.setText("30002");
    main_layout.addWidget(&this->port_edit, 0, 3);

    this->state_label.setText("have no connected");
    main_layout.addWidget(&this->state_label, 1, 2, 1, 2);

    main_layout.addWidget(&this->disconnect_btn, 2, 0);

    main_layout.addWidget(&this->connect_btn, 2, 3);

    this->paintor.setFixedSize(500, 400);
    main_layout.addWidget(&this->paintor, 3, 0, 3, 4);

    main_layout.addWidget(&this->clean_btn, 6, 0);
    main_layout.addWidget(&this->paint_btn, 6, 3);

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

    this->show();
}
