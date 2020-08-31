#include "MainWindow.h"

#include <qmessagebox.h>

#include <string>

#include "URDriver.h"

MainWindow::MainWindow(QWidget* ptr) : QWidget(ptr) {
    init_interface();
    init_event();
    this->show();
}

void MainWindow::init_interface() {
    QHBoxLayout* layer = new QHBoxLayout{};
    main_layer.addLayout(layer);
    layer->addWidget(new QLabel{"host:"});
    layer->addWidget(&this->ip_edit);
    layer->addWidget(new QLabel{":"});
    layer->addWidget(&this->port_edit);

    main_layer.addWidget(&this->connect_state);

    layer = new QHBoxLayout{};
    main_layer.addLayout(layer);
    layer->addWidget(&this->connect_btn);
    layer->addWidget(&this->disconnect_btn);

    for (int i = 0; i < this->joint_cnt; ++i) {
        auto* _lyt = new QHBoxLayout{};
        main_layer.addLayout(_lyt);
        _lyt->addWidget(
            new QLabel{("joint " + std::to_string(i) + ":").c_str()});
        _lyt->addWidget(&joint_edits[i]);
        _lyt->addWidget(new QLabel{"~"});
    }

    main_layer.addWidget(&this->movej_btn);

    for (int i = 0; i < this->movel_lab_cnt; ++i) {
        auto* _lyt = new QHBoxLayout{};
        main_layer.addLayout(_lyt);
        _lyt->addWidget(new QLabel{movel_lab_names[i]});
        _lyt->addWidget(&movel_edits[i]);
    }

    main_layer.addWidget(&this->movel_btn);
}

void MainWindow::init_event() {
    URDriver::get_instance().connect_callback_func = [this]() mutable {
        this->connect_state.setText("already!!");
        this->is_connected = true;
    };
    URDriver::get_instance().disconnect_callback_func = [this]() mutable {
        this->connect_state.setText("haved no connected");
        this->is_connected = false;
    };

    QObject::connect(
        &this->connect_btn, SIGNAL(clicked()), this, SLOT(connect_to_robot()));

    QObject::connect(&this->disconnect_btn,
                     SIGNAL(clicked()),
                     this,
                     SLOT(disconnect_from_robot()));

    QObject::connect(&this->movej_btn, SIGNAL(clicked()), this, SLOT(movej()));
    QObject::connect(&this->movel_btn, SIGNAL(clicked()), this, SLOT(movel()));
}

void MainWindow::connect_to_robot() {
    qInfo() << "to connect";
    if (!is_connected) {
        URDriver::get_instance().connectToRobot(
            QString::fromStdString(this->get_ip()), this->get_port());
    }
}

void MainWindow::disconnect_from_robot() {
    qInfo() << "to disconnect!";
    if (is_connected) {
        URDriver::get_instance().disconnetToRobot();
    }
}

void MainWindow::movej() {
    qInfo() << "movej";
    float joints[6];
    for (int i = 0; i < 6; ++i) {
        joints[i] = tool::stof(this->joint_edits[i].text().toStdString());
    }
    float a = 0.1f;
    float v = 0.1f;
    URDriver::get_instance().eval_by_qstring(
        tool::make_movej_script(joints, a, v));
}

void MainWindow::movel() {
    qInfo() << "movel";
    float pose[6];
    for (int i = 0; i < 6; ++i) {
        pose[i] = tool::stof(this->joint_edits[i].text().toStdString());
    }
    float a = 0.1f;
    float v = 0.1f;
    URDriver::get_instance().eval_by_qstring(
        tool::make_movel_script(pose, a, v));
}

std::string MainWindow::get_ip() {
    return this->ip_edit.text().toStdString();
}

int MainWindow::get_port() {
    return tool::stoi(this->port_edit.text().toStdString(), 80);
}
