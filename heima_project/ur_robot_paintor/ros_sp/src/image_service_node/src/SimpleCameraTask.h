#pragma once

#include <qobjectdefs.h>
#include <sensor_msgs/Image.h>

#include <functional>

#include "MyTask.h"
#include "ros/subscriber.h"

class SimpleCameraTask : public MyTask {
    Q_OBJECT
      public:
    static void callback(sensor_msgs::ImageConstPtr);
    ros::Subscriber subscriber;
    int run_goal();
    virtual void cancel() override;
};
