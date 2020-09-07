#include "TestWindow.h"

#include <qnamespace.h>
#include <qobjectdefs.h>

#include <exception>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <thread>

#include "about_svg_utils.hpp"
#include "cv_bridge/cv_bridge.h"
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

    main_lyt->addWidget(&state_lab, row, 0, 1, 4, Qt::AlignCenter);

    row++;

    main_lyt->addWidget(&connect_btn, row, 0, Qt::AlignLeft);
    main_lyt->addWidget(&disconnect_btn, row, 3, Qt::AlignRight);

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

    info_lab.setWordWrap(true);
    main_lyt->addWidget(&info_lab, row, 0, 1, 4);
}
void TestWindow::_init_event() {
    QObject::connect(this,
                     SIGNAL(info_out(const std::string&)),
                     this,
                     SLOT(on_info_out(const std::string&)));

    QObject::connect(&opencap_btn, SIGNAL(clicked()), this, SLOT(on_opencap()));

    QObject::connect(&closecap_btn, &QPushButton::clicked, [this]() {
        this->subscriber.shutdown();
        cv::destroyAllWindows();
    });

    QObject::connect(&opensvg_btn, SIGNAL(clicked()), this, SLOT(on_opensvg()));
}

void TestWindow::simple_cap_test_callback(
    const sensor_msgs::ImageConstPtr& ptr) {
    auto im = cv_bridge::toCvCopy(*ptr, sensor_msgs::image_encodings::BGR8);
    cv::imshow("info", im->image);
    // if ('\x1b' == cv::waitKey(120)) {
    // TestWindow::get_instance().subscriber.shutdown();
    // emit TestWindow::get_instance().info_out("info shutdown");
    //}
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

void TestWindow::on_opensvg() {
    emit info_out("on opensvg");
    new std::thread([this]() {
        auto server_name =
            loadQString(svgservername_edit, "svg_to_ways_server").toStdString();
        auto file_path =
            loadQString(svgfilepath_edit, "/home/tad/Picture/svg_s/8.svg")
                .toStdString();
        auto client =
            node->serviceClient<my_robot_move_msgs::SvgToPntss>(server_name);

        if (!client.waitForExistence(ros::Duration(5))) {
            emit info_out("has not been adverised,timeout 5 seconds");
            return;
        }

        my_robot_move_msgs::SvgToPntss obj;

        boost::property_tree::ptree pt;
        try {
            boost::property_tree::read_xml(file_path, pt);
        } catch (std::exception& e) {
            emit info_out(e.what());
            return;
        }

        auto pathd             = utils::get_pathd_from_doc(pt);
        auto sz                = utils::get_size_from_doc(pt);
        obj.request.ori_x      = 0;
        obj.request.ori_y      = 0;
        obj.request.ori_z      = 0.029;
        obj.request.rx         = 3.14;
        obj.request.ry         = 0.0;
        obj.request.rz         = 0.0;
        obj.request.tran_z     = 0.049;
        obj.request.width      = sz.first;
        obj.request.height     = sz.second;
        obj.request.svg_width  = sz.first;
        obj.request.svg_height = sz.second;
        obj.request.svg_pathds = *pathd;

        if (client.call(obj)) {
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
        }
		client.shutdown();
    });
}
