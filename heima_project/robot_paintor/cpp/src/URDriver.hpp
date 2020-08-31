#pragma once

#include <ctype.h>
#include <qobject.h>

#include <QString>
#include <QTcpSocket>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "utils.hpp"

union URData {
    std::uint8_t _data[1108];
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
    URData() = default;

    URData(const QByteArray& data) {
        size_t sz = std::min(sizeof(*this), (size_t)data.size());
        memcpy(this, data.data(), sz);
        this->MsgSize   = utils::reverse_value(this->MsgSize);
        std::uint8_t* p = &(_data[0]);
        for (std::uint8_t* q = p + 4; q < p + 1108 - 8; q += 8) {
            utils::reverse_byte(q, 8);
        }
    }
};

//枚举
enum MOVETYPE { MOVEJ, MOVEL, STOP };

//指令结构体
struct Instruction {
    MOVETYPE movetype;
    double data[6];
    double a;
    double v;

    Instruction() = default;
    Instruction(MOVETYPE t, double (&d)[6], double a, double v)
        : movetype{t}, a{a}, v{v} {
        memcpy(data, d, sizeof(double) * 6);
    }

    bool close_with(URData& ur_data, float epsilon = 0.018) {
        if (movetype == MOVETYPE::MOVEJ) {
            return std::abs(utils::variance(data, ur_data.q_actual)) <= epsilon;
        } else if (movetype == MOVETYPE::MOVEL) {
            return std::abs(utils::variance(
                       data, ur_data.Tool_vector_actual)) <= epsilon;
        } else {
            return true;
        }
    }
};

struct URDriver : public QObject {
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

    void movej(double (&joints)[6], double a = 0.1, double v = 0.1) {
        this->__queue.push(Instruction{MOVETYPE::MOVEJ, joints, a, v});
    }

    void movel(double (&pose)[6], double a = 0.1, double v = 0.1) {
        this->__queue.push({MOVETYPE::MOVEL, pose, a, v});
    }

    void stop_all() {
        while (this->__queue.empty() == false) {
            this->__queue.pop();
        }
        this->__is_doing = false;
    }

    void do_cmd_at_once(Instruction& ins) {
        std::cout << "do_cmd_at_once!" << std::endl;
        if (ins.movetype == MOVETYPE::MOVEJ) {
            this->movej_at_once(*utils::arr2vec(__queue.front().data),
                                __queue.front().a,
                                __queue.front().v);

        } else if (ins.movetype == MOVETYPE::MOVEL) {
            this->movel_at_once(*utils::arr2vec(__queue.front().data),
                                __queue.front().a,
                                __queue.front().v);
        }
    }

    void write_to_robot_at_once(const QString& cmd) {
        if (!__is_connected) {
            return;
        }
        std::cout << __func__ << ";" << __LINE__ << std::endl;
        std::cout << cmd.toStdString() << std::endl;
        socket.write(cmd.toUtf8());
    }

    void movej_at_once(std::vector<double>& joints,
                       double a = 0.1,
                       double v = 0.1) {
        write_to_robot_at_once(QString::fromStdString(movej_str(joints, a, v)));
    }

    std::string movej_str(std::vector<double>& joints,
                          double a = 0.1,
                          double v = 0.1) {
        std::stringstream ss;
        ss << "movej([" << utils::joint(",", joints).toStdString()
           << "],a=" << a << ",v=" << v << ",t=0,r=0)"
           << "\n"
           << std::endl;

        return ss.str();
    }

    void movel_at_once(std::vector<double>& pose,
                       double a = 0.1,
                       double v = 0.1) {
        write_to_robot_at_once(QString::fromStdString(movel_str(pose, a, v)));
    }

    std::string movel_str(std::vector<double>& pose,
                          double a = 0.1,
                          double v = 0.1) {
        std::stringstream ss;
        ss << "movel(p[" << utils::joint(",", pose).toStdString() << "],a=" << a
           << ",v=" << v << ",t=0,r=0)"
           << "\n"
           << std::endl;
        return ss.str();
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

        QObject::connect(&this->socket,
                         &QTcpSocket::readyRead,
                         this,
                         &URDriver::readyRead_callback);
    }
    URDriver(const URDriver&) = delete;
    URDriver& operator=(const URDriver&) = delete;

      protected:
    void do_next_cmd(URData& ur_data) {
        if (this->__queue.empty()) {
            __is_doing = false;
            return;
        }
        if (__is_doing == false) {
            this->do_cmd_at_once(this->__queue.front());
            __is_doing = true;
            return;
        }

        if (__is_doing == true) {
            if (this->__queue.front().close_with(ur_data)) {
                __is_doing = false;
                this->__queue.pop();
            }
        }
    }

    void readyRead_callback() {
        QByteArray data = socket.readAll();
        URData ur_data{data};
        do_next_cmd(ur_data);
    }

      private:
    QTcpSocket socket;

    std::atomic_bool __is_connected{false};
    std::atomic_bool __is_doing{false};

    std::queue<Instruction> __queue;
};
