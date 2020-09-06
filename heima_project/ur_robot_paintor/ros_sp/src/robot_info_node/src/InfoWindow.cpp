#include "InfoWindow.h"

#include <qlabel.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <tf/transform_datatypes.h>

#include <QGridLayout>

#include "geometry_msgs/PoseStamped.h"
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

    main_layout->addWidget(&this->state_lab, 1, 0, 1, 4, Qt::AlignRight);

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

    QObject::connect(this, SIGNAL(destroyed()), this, SLOT(close()));

    QObject::connect(&this->socket, &QTcpSocket::connected, [this]() {
        this->state_lab.setText("connected");
    });
    QObject::connect(&this->socket, &QTcpSocket::disconnected, [this]() {
        this->state_lab.setText("out line");
    });
    QObject::connect(
        &this->socket, SIGNAL(readyRead()), this, SLOT(readyread_callback()));

    QObject::connect(&this->disconnect_btn, &QPushButton::clicked, [this]() {
        this->socket.disconnectFromHost();
    });
    QObject::connect(&this->connect_btn, &QPushButton::clicked, [this]() {
        this->socket.connectToHost(this->ip_edit.text(),
                                   this->port_edit.text().toInt());
    });
}

void InfoWindow::close() {
    if (nullptr != this->node) {
        this->node->shutdown();
    }
}

void InfoWindow::readyread_callback() {
    QByteArray bytes = socket.readAll();
    URData data{bytes};
    for (int i = 0; i < 6; i++) {
        this->pose_lab[i].setText(QString::number(data.Tool_vector_actual[i]));
    }
    if (nullptr == publisher) {
        return;
    }

    geometry_msgs::PoseStamped pose;

    pose.pose.position.x = data.Tool_vector_actual[0];
    pose.pose.position.y = data.Tool_vector_actual[1];
    pose.pose.position.z = data.Tool_vector_actual[2];

    tf::Quaternion ori =
        tf::createQuaternionFromRPY(data.Tool_vector_actual[3],
                                    data.Tool_vector_actual[4],
                                    data.Tool_vector_actual[5]);
    pose.pose.orientation.w = ori.w();
    pose.pose.orientation.x = ori.x();
    pose.pose.orientation.y = ori.y();
    pose.pose.orientation.z = ori.z();

    publisher->publish(pose);
}
