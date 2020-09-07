#pragma once

#include <cv_bridge/cv_bridge.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <sensor_msgs/Image.h>

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "ros/node_handle.h"
#include "ros/subscriber.h"

class TestWindow : public QWidget {
    Q_OBJECT
    TestWindow();
    TestWindow(const TestWindow&) = delete;
    TestWindow operator=(const TestWindow&) = delete;

    ros::NodeHandle* node{nullptr};

    QLineEdit host_edit, port_edit;
    QPushButton connect_btn{"connect"}, disconnect_btn{"disconnect"};
    QLabel state_lab;

    QPushButton opencap_btn{"open capture"};
    QLineEdit topic_name_edit;
    QPushButton closecap_btn{"close capture"};

    QPushButton opensvg_btn{"open svg"};
    QLineEdit svgservername_edit;
    QLineEdit svgfilepath_edit;

    QLabel info_lab;

    void _init_virsual();
    void _init_event();

      protected:
    virtual ~TestWindow() {
    }

    ros::Subscriber subscriber;
    static void simple_cap_test_callback(const sensor_msgs::ImageConstPtr& ptr);

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

    void set_node(ros::NodeHandle& node) {
        this->node = &node;
    }

      signals:
    void info_out(const std::string&);
      protected slots:
    void on_opencap();
    void on_info_out(const std::string&);

    void on_opensvg();
};
