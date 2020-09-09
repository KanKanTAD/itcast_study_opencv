#pragma once

#include <ros/ros.h>

#include <QObject>

class MyTask : public QObject {
    Q_OBJECT
      public:
    ros::NodeHandle* node{nullptr};
    std::string server_name;

    virtual void cancel() = 0;
};
