#include <AuboRobotMetaType.h>
#include <serviceinterface.h>

#include <functional>
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char** argv) {
    std::cout << "argc:" << argc << std::endl;
    std::string host{"127.0.0.1"};
    int port = 8899;
    std::string username{"aubo"};
    std::string password{"1"};
    if (argc >= 2) {
        host = argv[1];
    }
    if (argc >= 3) {
        port = std::stoi(argv[2]);
    }

    if (argc >= 4) {
        username = argv[3];
    }
    if (argc >= 5) {
        username = argv[4];
    }

    ServiceInterface robot_service;

    int res = robot_service.robotServiceLogin(
        host.c_str(), port, username.c_str(), password.c_str());

    if (res == aubo_robot_namespace::InterfaceCallSuccCode) {
        std::cout << "login success!" << std::endl;
    } else {
        std::cout << "login fails!" << std::endl;
    }

    std::unique_ptr<int, std::function<void(int*)>> _0x1{
        &res, [&](int* a) {
            if (res == aubo_robot_namespace::InterfaceCallSuccCode) {
                robot_service.robotServiceLogout();
                std::cout << "logout!" << std::endl;
            }
        }};

    return 0;
}
