#include "MoveURDriver.h"

#include <qobjectdefs.h>

#include "SimpleURDriver.h"
#include "my_robot_move_msgs/PainterMoveFeedback.h"
#include "my_robot_move_msgs/Point.h"

MoveURDriver::MoveURDriver(const std::string& host, int port)
    : SimpleURDriver(host, port) {
}

void MoveURDriver::run_goal0(GoalHandle_t handle) {
    auto& ways = handle.getGoal()->ways.data;
    qInfo() << "ways size:" << handle.getGoal()->ways.data.size() << __func__;
    // for (auto& p : ways) {
    // qInfo() << p.x << " " << p.y << " " << p.z << " " << p.rx << " " << p.ry
    //<< " " << p.rz;
    //}

    this->handle = handle;
    _set_driver_event();
    emit this->connect_to_host();
}

void MoveURDriver::_set_driver_event() {
    this->on_connected_func = [this]() {
        ROS_INFO_STREAM("connect to '" + this->host + ":" +
                        std::to_string(this->port) + "' successed!");
        this->idx      = 0;
        this->prev_idx = this->idx - 1;
    };

    this->on_disconnected_func = [this]() {
        ROS_INFO_STREAM("disconnect from '" + this->host + ":" +
                        std::to_string(this->port) + "' successed!");
        handle.setAborted();
        this->on_goal_aborted_func();
    };

    this->on_readyread_func = [this]() {
        my_robot_move_msgs::PainterMoveFeedback feedback;
        auto code = this->run_next();
        if (-1 == code) {
            this->on_goal_aborted_func();
        } else if (1 == code) {
            this->on_goal_successed_func();
        }
        auto& ways = this->handle.getGoal()->ways.data;
        feedback.percent =
            100.0f * ((float)this->idx + 1.0f) / ((float)ways.size() + 1.0f);
        // qInfo() << "percent->" << feedback.percent;
        feedback.code = code;
        if (idx < ways.size()) feedback.current_pose = ways.at(idx);
        handle.publishFeedback(feedback);
    };

    this->on_error_func = [this](QAbstractSocket::SocketError er) {
        ROS_INFO_STREAM("error from '" + this->host + ":" +
                        std::to_string(this->port) + "' " + std::to_string(er));

        handle.setAborted();
        this->on_goal_aborted_func();
    };
}

int MoveURDriver::run_next() {
    auto goal     = handle.getGoal();
    auto& ways    = goal->ways.data;
    auto& epsilon = goal->epsilon;
    if (idx >= ways.size()) {
        return 1;
    }
    if (idx < 0) {
        return -1;
    }

    my_robot_move_msgs::Point pnt = ways.at(idx);
    auto er                       = movel_error(this->ur_data, pnt);
    auto s                        = get_movel_str(pnt.x,
                           pnt.y,
                           pnt.z,
                           pnt.rx,
                           pnt.ry,
                           pnt.rz,
                           goal->acceleration,
                           goal->velocity);
    qInfo() << tr(s.c_str()) << " in idx_" << idx << "********** error:" << er
            << " -- epsilon:" << epsilon;
    if (er <= epsilon) {
        idx++;
    } else {
        // qInfo() << tr(s.c_str()) << " in idx_" << idx;
        emit this->print(s);
    }
    if (idx != prev_idx) {
        prev_idx = idx;
        // qInfo() << tr(s.c_str()) << " in idx_" << idx
        //<< "********** error:" << er << " -- epsilon:" << epsilon;
    }
    return 0;
}

double MoveURDriver::angle_distance(double a, double b) {
    std::complex<double> c1{0, a};
    std::complex<double> c2{0, b};
    c1     = std::exp(c1);
    c2     = std::exp(c2);
    auto c = c1 / c2;
    return std::abs(std::log(c));
}

double MoveURDriver::movel_error(URData& data, my_robot_move_msgs::Point& pnt) {
    double a          = 0.0;
    auto& curren_pose = data.Tool_vector_actual;
    a += std::pow(pnt.x - curren_pose[0], 2);
    a += std::pow(pnt.y - curren_pose[1], 2);
    a += std::pow(pnt.z - curren_pose[2], 2);
    double b = 0.0;
    b += angle_distance(pnt.rx, curren_pose[3]);
    b += angle_distance(pnt.ry, curren_pose[4]);
    b += angle_distance(pnt.rz, curren_pose[5]);
    double c = std::sqrt(a) * 0.5 + b / 3.0 * 0.5;
    return c;
}

std::string MoveURDriver::get_movel_str(float x,
                                        float y,
                                        float z,
                                        float rx,
                                        float ry,
                                        float rz,
                                        float a,
                                        float v) {
    std::stringstream ss;
    ss << "movel(p[" << x << "," << y << "," << z << "," << rx << "," << ry
       << "," << rz << "],t=0,r=0,a=" << a << ",v=" << v << ")\n";
    return ss.str();
}
