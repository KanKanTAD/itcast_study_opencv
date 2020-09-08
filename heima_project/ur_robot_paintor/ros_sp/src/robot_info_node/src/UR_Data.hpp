#pragma once

#include <QByteArray>
#include <algorithm>
#include <cmath>
#include <complex>
#include <iterator>
#include <numeric>

struct URData {
    union {
        int MsgSize;  // 121
        uint8_t msg_size_data[4];
    };
    union {
        uint8_t double_byte_data[1108 - 4];
        double double_arr[138];
        struct {
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

    static void set_by_qbytearray(URData& self, QByteArray& data) {
        memcpy(&self.MsgSize, data.data(), 4);
        std::reverse(std::begin(self.msg_size_data),
                     std::end(self.msg_size_data));
        memcpy(self.double_byte_data,
               data.data() + 4,
               sizeof(self.double_byte_data));
        for (int i = 0; i < sizeof(self.double_byte_data); i += 8) {
            for (int j = 0; j < 4; j++) {
                std::swap(self.double_byte_data[i + j],
                          self.double_byte_data[i + 7 - j]);
            }
        }
    }

    URData() = default;

    URData(QByteArray& data) {
        URData::set_by_qbytearray(*this, data);
    }

    QByteArray& toQByteArray(QByteArray& data) {
        data.clear();
        std::copy(std::begin(this->msg_size_data),
                  std::end(this->msg_size_data),
                  std::back_inserter(data));
        std::copy(std::begin(this->double_byte_data),
                  std::end(this->double_byte_data),
                  std::back_inserter(data));
        return data;
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

    bool close_with(URData& ur_data, float epsilon = 0.0018) {
        double res = epsilon;
        if (movetype == MOVETYPE::MOVEJ) {
            res = 0.0;
            for (int i = 0; i < 6; i++) {
                res += std::pow(this->data[i] - ur_data.q_actual[i], 2);
            }
            res = std::sqrt(res);
        } else if (movetype == MOVETYPE::MOVEL) {
            float a = 0.0f;
            for (int i = 0; i < 3; i++) {
                a += std::pow(this->data[i] - ur_data.Tool_vector_actual[i], 2);
            }
            a       = std::sqrt(a);
            float b = 0.0f;
            for (int i = 3; i < 6; ++i) {
                std::complex<double> c1{0, this->data[i]};
                c1 = std::exp(c1);
                std::complex<double> c2{0,
                                        ur_data.Tool_Accelerometer_values[i]};
                c2     = std::exp(c2);
                auto c = c1 / c2;
                b += std::abs(std::log(c));
            }
            b /= 3.0f;
            res = (a + b) / 2.0f;
        } else {
            return true;
        }
        // std::cout << "error: " << res << " <--> epsilon:" << epsilon
        //<< std::endl;
        return res <= epsilon;
    }
};
