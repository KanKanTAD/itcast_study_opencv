#pragma once

#include <qobjectdefs.h>
#include <unistd.h>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QWidget>

#include "UR_Data.hpp"
#include "ros/node_handle.h"
#include "ros/publisher.h"

class InfoWindow : public QWidget {
    Q_OBJECT

      public:
    virtual ~InfoWindow() {
    }
    InfoWindow(QWidget* ptr = nullptr);

    void set_rosnode(ros::NodeHandle& node) {
        this->node = &node;
    }
    void set_publisher(ros::Publisher& publisher) {
        this->publisher = &publisher;
    }

      private:
    ros::NodeHandle* node{nullptr};
    ros::Publisher* publisher{nullptr};

    QPushButton connect_btn{"connect"}, disconnect_btn{"disconnect"};
    QLabel state_lab;
    QLineEdit ip_edit, port_edit;
    QLabel pose_lab[6];
    QTcpSocket socket;

      protected slots:
    void close();
    void readyread_callback();
};
