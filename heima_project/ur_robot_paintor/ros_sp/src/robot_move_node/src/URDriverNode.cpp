#include "URDriverNode.h"

#include <qabstractsocket.h>
#include <qobjectdefs.h>

#include <QAbstractSocket>
#include <QDataStream>
#include <chrono>
#include <cmath>
#include <complex>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include "UR_Data.hpp"
#include "my_robot_move_msgs/PainterMoveFeedback.h"
#include "my_robot_move_msgs/PainterMoveResult.h"
#include "my_robot_move_msgs/Point.h"
#include "ros/node_handle.h"

static inline double angle_distance(double a, double b) {
    std::complex<double> c1{0, a};
    std::complex<double> c2{0, b};
    c1     = std::exp(c1);
    c2     = std::exp(c2);
    auto c = c1 / c2;
    return std::abs(std::log(c));
}

URDriverNode::URDriverNode(ros::NodeHandle& node,
                           const std::string& server_name)
    : node{node}, server_name{server_name} {
    // qRegisterMetaType<my_robot_move_msgs::Point>("my_robot_move_msgs::Point");
    action_server.reset(new ActionServer_t(this->node, server_name, false));

    action_server->registerCancelCallback(boost::bind(
        &URDriverNode::cancel_callback, this, boost::placeholders::_1));
    action_server->registerGoalCallback(boost::bind(
        &URDriverNode::goal_callback, this, boost::placeholders::_1));
    action_server->start();

    QObject::connect(
        this,
        SIGNAL(
            movel_to(float, float, float, float, float, float, float, float)),
        this,
        SLOT(on_movel_to(
            float, float, float, float, float, float, float, float)));
    QObject::connect(this,
                     SIGNAL(connect_socket_event()),
                     this,
                     SLOT(on_connect_socket_event()));
    QObject::connect(
        this, SIGNAL(connect_to_host()), this, SLOT(on_connect_to_host()));
}

void URDriverNode::goal_callback(GoalHandle_t handle) {
    ROS_INFO_STREAM("got it");
    handle.setAccepted();
    goal_handle = handle;
    emit this->connect_socket_event();
    // socket.connectToHost(QString::fromStdString(goal->host), goal->port);
    emit this->connect_to_host();
}
void URDriverNode::cancel_callback(GoalHandle_t handle) {
    handle.setCanceled();
    emit socket.disconnected();
}

void URDriverNode::on_connected() {
    ROS_INFO_STREAM("connected!!!");
    is_running = true;
    new std::thread([this]() {
        auto goal  = goal_handle.getGoal();
        auto& ways = goal->ways.data;
        float sz   = ways.size();
        float cnt  = 0;
        for (const my_robot_move_msgs::Point& way : ways) {
            cnt += 1.0f;
            while (error(way) > goal->epsilon) {
                if (is_running == false) {
                    goal_handle.setAborted();
                    break;
                }
                emit this->movel_to(way.x,
                                    way.y,
                                    way.z,
                                    way.rx,
                                    way.ry,
                                    way.rz,
                                    goal->acceleration,
                                    goal->velocity);
                my_robot_move_msgs::PainterMoveFeedback feedback;
                feedback.current_pose = way;
                feedback.percent      = cnt / sz;
                goal_handle.publishFeedback(feedback);
                std::this_thread::sleep_for(std::chrono::milliseconds(60));
            }
        }
        my_robot_move_msgs::PainterMoveResult result;
        result.code   = 200;
        result.result = "ok!";
        goal_handle.setSucceeded(result);
    });
}

void URDriverNode::on_disconnected() {
    is_running = false;
}

void URDriverNode::on_error() {
    ROS_INFO_STREAM("error!!");
    goal_handle.setAborted();
    is_running = false;
}

void URDriverNode::on_readyread() {
    auto bytes = socket.readAll();
    URData data{bytes};
    // URData data;
    // memcpy(data.msg_size_data, bytes.data(), 4);
    // memcpy(
    // data.double_byte_data, bytes.data() + 4, sizeof(data.double_byte_data));
    memcpy(
        this->curren_pose, data.Tool_vector_actual, sizeof(this->curren_pose));
    char buff[1024];
    sprintf(buff,
            "%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f",
            curren_pose[0],
            curren_pose[1],
            curren_pose[2],
            curren_pose[3],
            curren_pose[4],
            curren_pose[5]);
    // ROS_INFO_STREAM(buff);
}

double URDriverNode::error(const my_robot_move_msgs::Point& pnt) {
    double a = 0.0;
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

bool URDriverNode::join_movel_util(const my_robot_move_msgs::Point& pnt,
                                   double epsilon) {
    while (is_running == true) {
        auto c = error(pnt);
        char buff[1024];
        sprintf(buff, "error: %3.3f <--> epsilon:%3.3f", c, epsilon);
        // ROS_INFO_STREAM(buff);
        if (c <= epsilon) {
            return true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
    return false;
}

void URDriverNode::on_movel_to(float x,
                               float y,
                               float z,
                               float rx,
                               float ry,
                               float rz,
                               float a,
                               float v) {
    std::stringstream ss;
    ss << "movel(p[" << x << "," << y << "," << z << "," << rx << "," << ry
       << "," << rz << "],a=" << a << ",v=" << v << ",t=0,r=0)\n";
    ROS_INFO_STREAM("on_move_to->" + ss.str());

    socket.write(QString::fromStdString(ss.str()).toUtf8());

    // QDataStream out{&socket};
    // out << "movel(p[" << x << "," << y << "," << z << "," << rx << "," << ry
    //<< "," << rz << "],a=" << a << ",v=" << v << ",t=0,r=0)\n";

    //// out << x << y << z << rx << ry << rz;
    // socket.flush();
}

void URDriverNode::on_connect_socket_event() {
    std::call_once(__once, [this]() {
        QObject::connect(
            &socket, SIGNAL(connected()), this, SLOT(on_connected()));
        QObject::connect(
            &socket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
        QObject::connect(&socket,
                         SIGNAL(error(QAbstractSocket::SocketError)),
                         this,
                         SLOT(on_error()));
        QObject::connect(
            &socket, SIGNAL(readyRead()), this, SLOT(on_readyread()));
    });
}

void URDriverNode::on_connect_to_host() {
    auto goal = goal_handle.getGoal();
    socket.connectToHost(QString::fromStdString(goal->host), goal->port);
}
