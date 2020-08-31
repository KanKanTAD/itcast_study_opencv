#pragma once

#include <QString>
#include <QTcpSocket>
#include <atomic>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "utils.hpp"

union URData {
    struct {
        int MsgSize;  // 121
        double Time;
        double q_target[6];
        double qd_target[6];
        double qdd_target[6];
        double I_target[6];
        double M_target[6];
        //当前关节角度
        double q_actual[6];
        double qd_actual[6];  //关节角度
        double I_actual[6];
        double I_control[6];
        //当前工具位置
        double Tool_vector_actual[6];
        double TCP_speed_actual[6];
        double TCP_force[6];
        double Tool_vector_target[6];
        double TCP_speed_target[6];
        double Digital_input_bits;
        double Motor_temperatures[6];
        double Controller_Timer;
        double Test_value;
        double Robot_Mode;
        double Joint_Modes[6];
        double Safety_Mode;
        double Buffer1[6];
        double Tool_Accelerometer_values[3];
        double Buffer2[6];
        double Speed_scaling;
        double Linear_momentum_norm;
        double Buffer3;
        double Buffer4;
        double V_main;
        double V_robot;
        double I_robot;
        double V_actual[6];
        double Digital_outputs;
        //机械臂状态：1 空闲  2 工作
        double Program_state;
        double Elbow_position[3];
        double Elbow_velocity[3];
    };
};

//枚举
enum MOVETYPE { MOVEJ, MOVEL };

//指令结构体
struct Instruction {
    MOVETYPE movetype;
    double data[6];
    double a;
    double v;
};

struct URDriver {
    std::function<void()> connect_callback_func;
    std::function<void()> disconnect_callback_func;

    static URDriver& get_instance() {
        static URDriver instance;
        return instance;
    }

    void connect_robot(const QString& ip, int port) {
        try {
            socket.connectToHost(ip, port);
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void disconnect_robot() {
        try {
            socket.disconnectFromHost();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    bool is_connected() {
        return __is_connected;
    }

    void write_to_robot(const QString& cmd) {
        if (!__is_connected) {
            return;
        }
        socket.write(cmd.toUtf8());
    }

    void movej(std::vector<double>& joints, double a = 0.1, double v = 0.1) {
        std::stringstream ss;
        ss << "movej([" << utils::joint(",", joints) << "],a=" << a
           << ",v=" << v << "t=1"
           << "c=1"
           << "\n"
           << std::endl;
    }

      private:
    URDriver() {
        QObject::connect(&this->socket, &QTcpSocket::connected, [this]() {
            this->__is_connected = true;
            this->connect_callback_func();
        });

        QObject::connect(&this->socket, &QTcpSocket::disconnected, [this]() {
            this->__is_connected = false;
            this->disconnect_callback_func();
        });

        // QObject::connect(&this->socket,&QTcpSocket::
    }
    URDriver(const URDriver&) = delete;
    URDriver& operator=(const URDriver&) = delete;

    QTcpSocket socket;

    std::atomic_bool __is_connected{false};
};
