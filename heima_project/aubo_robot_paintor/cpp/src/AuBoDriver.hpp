#pragma once
#include <serviceinterface.h>

#include <QString>
#include <exception>
#include <functional>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

#include "Paintor.h"
#include "utils.hpp"

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

    bool close_with(double (&arg)[6], float epsilon = 0.0018) {
        double res = epsilon;
        if (movetype == MOVETYPE::MOVEJ) {
            res = utils::eular_distance(data, arg);
        } else if (movetype == MOVETYPE::MOVEL) {
            std::cout << "target to->";
            for (int i = 0; i < 6; i++) {
                std::cout << data[i] << " ,";
            }
            res = utils::movel_error(data, arg);
        } else {
            return true;
        }
        std::cout << "error: " << res << " <--> epsilon:" << epsilon
                  << std::endl;
        return res <= epsilon;
    }
};

struct AuBoDriver {
    double current_pose[6];
    int state      = {-999};
    double epsilon = {0.018};
    ServiceInterface robot_service;

    std::function<void(const aubo_robot_namespace::wayPoint_S&)>
        way_point_callback_func;

    static AuBoDriver& get_instance() {
        static AuBoDriver instance;
        return instance;
    }

    static void RealTimeWaypointCallback(
        const aubo_robot_namespace::wayPoint_S* wayPointPtr,
        void* arg) {
        if (nullptr != wayPointPtr) {
            for (int i = 0; i < 3; i++) {
                AuBoDriver::get_instance().current_pose[i] =
                    wayPointPtr->cartPos.positionVector[i];
            }
            aubo_robot_namespace::Rpy r;
            AuBoDriver::get_instance().robot_service.quaternionToRPY(
                wayPointPtr->orientation, r);
            AuBoDriver::get_instance().current_pose[3] = r.rx;
            AuBoDriver::get_instance().current_pose[4] = r.ry;
            AuBoDriver::get_instance().current_pose[5] = r.rz;

            AuBoDriver::get_instance().do_next_cmd(
                AuBoDriver::get_instance().current_pose);

            AuBoDriver::get_instance().way_point_callback_func(*wayPointPtr);
        }
    }

    std::atomic_bool is_stop_move_batch{false};

    void stop_move_batch() {
        is_stop_move_batch = true;
    }
    void move_batch(MOVETYPE mtype,
                    std::vector<std::vector<double>>* pts_s,
                    double a,
                    double v) {
        if (is_stop_move_batch == false) {
            return;
        }
        std::cout << __func__ << ":" << __FILE__ << "-" << __LINE__
                  << std::endl;

        is_stop_move_batch = false;

        new std::thread([mtype, pts_s, a, v]() mutable {
            auto* ptss = pts_s;
            if (ptss == nullptr) {
                return;
            }

            std::cout << "ptss size:" << ptss->size() << std::endl;
            int _0x2;
            std::unique_ptr<int, std::function<void(int*)>> _0x1{
                &_0x2, [&](int* a) mutable {
                    if (nullptr != ptss) {
                        delete ptss;
                    }
                    AuBoDriver::get_instance().stop_move_batch();
                    std::cout << "return from move_batch !" << std::endl;
                }};
            for (int i = 0; i < ptss->size(); i++) {
                std::cout << i << std::endl;
                if (mtype == MOVETYPE::MOVEL) {
                    AuBoDriver::get_instance().movel_at_once(
                        ptss->at(i), a, v, true);
                }
                if (AuBoDriver::get_instance().is_stop_move_batch == true) {
                    return;
                }
            }
        });
    }

    void stop_all() {
        stop_move_batch();
        try {
            this->clear_queue();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    void movej_at_once(double (&joint)[6], double a = 0.12, double v = 0.25) {
    }
    void movel_at_once(std::vector<double>& pose,
                       double a     = 0.12,
                       double v     = 0.25,
                       bool IsBolck = true) {
        std::cout << __func__ << ":" << __LINE__ << "--->";
        for (double& p : pose) {
            std::cout << p << " ,";
        }
        std::cout << "  a:" << a << "  v:" << v << std::endl;
        if (pose.size() < 6) {
            return;
        }
        double _pose[6];
        for (int i = 0; i < 6; i++) {
            _pose[i] = pose[i];
        }
        movel_at_once(_pose, a, v);
    }
    void movel_at_once(double (&pose)[6],
                       double a     = 0.12,
                       double v     = 0.25,
                       bool IsBolck = true) {
        std::cout << __func__ << ":" << __LINE__ << std::endl;

        robot_service.robotServiceSetGlobalMoveEndMaxLineAcc(a);
        robot_service.robotServiceSetGlobalMoveEndMaxLineVelc(v);
        //位置
        aubo_robot_namespace::Pos position{pose[0], pose[1], pose[2]};
        //姿态 119.738899  -1.101317 -173.774994
        aubo_robot_namespace::Rpy rpy{pose[3], pose[4], pose[5]};
        //接收四元数的结果
        aubo_robot_namespace::Ori ori;
        //欧拉角转成四元数
        robot_service.RPYToQuaternion(rpy, ori);
        //定义vector接受反解结果
        std::vector<aubo_robot_namespace::wayPoint_S> wayPointVector;
        robot_service.robotServiceRobotIk(position, ori, wayPointVector);
        robot_service.robotServiceLineMove(wayPointVector[0], IsBolck);
    }
    void movel(double (&pose)[6], double a = 0.12, double v = 0.25) {
        this->__queue.push({MOVETYPE::MOVEL, pose, a, v});
    }

    void movej(double (&joint)[6], double a = 0.12, double v = 0.25) {
    }

    void connect_robot(const QString& ip, int port) {
        if (is_connected()) {
            return;
        }

        state = robot_service.robotServiceLogin(
            ip.toStdString().c_str(), port, "aubo", "123456");
        if (state != aubo_robot_namespace::InterfaceCallSuccCode) {
            std::cout << "connect fails!" << std::endl;
            return;
        }

        std::cout << "connect to robot ->" << ip.toStdString() << ":" << port
                  << "  ! successed!" << std::endl;
        new std::thread([this]() {
            aubo_robot_namespace::ToolDynamicsParam toolDynamicsParam;
            memset(&toolDynamicsParam, 0, sizeof(toolDynamicsParam));
            aubo_robot_namespace::ROBOT_SERVICE_STATE result;
            int ret = robot_service.rootServiceRobotStartup(
                toolDynamicsParam /**工具动力学参数**/,
                6 /*碰撞等级*/,
                true /*是否允许读取位姿　默认为true*/,
                true,    /*保留默认为true */
                1000,    /*保留默认为1000 */
                result); /*机械臂初始化*/
            if (ret == aubo_robot_namespace::InterfaceCallSuccCode) {
                std::cerr << "机械臂初始化成功." << std::endl;
            } else {
                std::cerr << "机械臂初始化失败." << std::endl;
            }

            robot_service.robotServiceRegisterRealTimeRoadPointCallback(
                AuBoDriver::RealTimeWaypointCallback, nullptr);
        });
    }

    void disconnect_robot() {
        if (!is_connected()) {
            return;
        }
        new std::thread(
            [this]() { robot_service.robotServiceRobotShutdown(); });
        robot_service.robotServiceLogout();
    }

    bool is_connected() {
        bool connectStatus;
        robot_service.robotServiceGetConnectStatus(connectStatus);
        return connectStatus;
    }

    void do_cmd_at_once(Instruction& ins) {
        // std::cout << __func__ << ":" << __LINE__ << std::endl;
        if (ins.movetype == MOVETYPE::MOVEJ) {
        } else if (ins.movetype == MOVETYPE::MOVEL) {
            this->movel_at_once(
                ins.data, __queue.front().a, __queue.front().v, false);
        }
    }

      protected:
    void clear_queue() {
        while (this->__queue.empty() == false) {
            this->__queue.pop();
        }
    }
    void do_next_cmd(double (&arg)[6]) {
        if (!is_connected()) {
            return;
        }
        // std::cout << __func__ << ":" << __LINE__ << std::endl;
        if (this->__queue.empty()) {
            // std::cout << "__queue.empty()" << std::endl;
            __is_doing = false;
            return;
        }
        if (__is_doing == false && this->__queue.empty() == false) {
            // std::cout << "doing false" << std::endl;
            this->do_cmd_at_once(this->__queue.front());
            __is_doing = true;
            return;
        }

        if (__is_doing == true) {
            // std::cout << "doing true" << std::endl;
            if (this->__queue.empty() ||
                this->__queue.front().close_with(current_pose, this->epsilon)) {
                std::cout << "close with" << std::endl;
                __is_doing = false;
                if (this->__queue.empty() == false) this->__queue.pop();
            }
            return;
        }
    }

      private:
    AuBoDriver() {
    }
    AuBoDriver(const AuBoDriver&) = delete;
    AuBoDriver& operator=(const AuBoDriver&) = delete;

    std::atomic_bool __is_doing{false};

    std::queue<Instruction> __queue;
};
