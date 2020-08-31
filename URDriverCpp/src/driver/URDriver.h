#pragma once

#include <qtcpsocket.h>

#include <QString>
#include <QTcpSocket>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

namespace tool {

inline int stoi(const std::string& s, int default_ = 0) {
    int res = default_;
    try {
        res = std::stoi(s);
    } catch (std::exception& e) {
    }
    return res;
}

inline float stof(const std::string& s, float default_ = 0.f) {
    float res = default_;
    try {
        res = std::stof(s);
    } catch (std::exception& e) {
    }
    return res;
}

inline float gra2deg(double gra) {
    return gra / 180.0 * M_PI;
}

inline float gra2deg(const std::string& gra) {
    return gra2deg(tool::stof(gra));
}
// degree to gradius
inline float deg2gra(double deg) {
    return deg / M_PI * 180.0;
}
inline float deg2gra(const std::string& deg) {
    return deg2gra(tool::stof(deg));
}

inline QString make_movej_script(const float (&joints)[6], float a, float v) {
    std::stringstream ss;
    ss << "movej([";
    ss << joints[0];
    for (int i = 1; i < 6; ++i) {
        ss << "," << joints[i];
    }
    ss << "],"
       << "a=" << a << ",v=" << v << ",t=0,r=0)\n"
       << std::endl;
    return QString::fromStdString(ss.str());
}

inline QString make_movel_script(const float (&pose)[6], float a, float v) {
    std::stringstream ss;
    ss << "movel(p[";
    ss << pose[0];
    for (int i = 1; i < 6; ++i) {
        ss << "," << pose[i];
    }
    ss << "],t=0,r=0,"
       << "a=" << a << ",v=" << v << ")\n"
       << std::endl;
    return QString::fromStdString(ss.str());
}

template <typename T>
inline T byte_reverse(T val) {
    const size_t sz = sizeof(val);
    std::uint8_t vs[sz];
    memcpy(vs, &val, sz);
    std::reverse(std::begin(vs), std::end(vs));
    val = *((T*)vs);
    return val;
}

}  // namespace tool

//连接上机械臂，机械臂返回的数据
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

class URDriver {
    URDriver();
    URDriver(const URDriver&) = delete;
    URDriver& operator=(const URDriver&) = delete;

    QTcpSocket socket;

      public:
    static URDriver& get_instance() {
        static URDriver _instance{};
        return _instance;
    }

    std::function<void()> connect_callback_func;
    std::function<void()> disconnect_callback_func;

    void connectToRobot(QString ip, int port);
    void disconnetToRobot();

    void eval_by_qstring(const QString& script);
};
