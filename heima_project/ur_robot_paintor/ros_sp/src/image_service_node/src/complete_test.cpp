#include <ros/ros.h>

#include <QApplication>
#include <chrono>
#include <string>
#include <thread>

#include "TestWindow.h"

int main(int argc, char** argv) {
    std::string node_name{"complete_test_node"};
    ros::init(argc, argv, node_name, ros::init_options::AnonymousName);

    ros::NodeHandle node;

    ros::AsyncSpinner spinner{0};
    spinner.start();

    QApplication a(argc, argv);

    new std::thread([&]() {
        while (ros::isShuttingDown() == false) {
            std::this_thread::sleep_for(std::chrono::milliseconds(120));
        }
        a.quit();
    });

    TestWindow::get_instance().set_node(node);

    return a.exec();
}
