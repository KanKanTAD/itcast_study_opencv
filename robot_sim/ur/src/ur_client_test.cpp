#include <qcoreapplication.h>
#include <qobject.h>
#include <qtcpsocket.h>

#include <QCoreApplication>
#include <QDataStream>
#include <QTcpSocket>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>

#include "UR_Data.hpp"

static double target0[6] = {100.0, 100, 100, 100, 100, 100};
double calc_error(double (&target)[6], URData& state) {
    double res = 0.0;
    for (int i = 0; i < 6; i++) {
        res += std::pow(target[i] - state.Tool_vector_actual[i], 2);
    }
    res /= 6.0;
    return res;
}

template <typename T>
inline T reverse_value(T v) {
    std::uint8_t data[sizeof(T)];
    memcpy(data, &v, sizeof(T));
    std::reverse(std::begin(data), std::end(data));
    return *((T*)(data));
}

int main(int argc, char** argv) {
    QCoreApplication app{argc, argv};
    QTcpSocket socket;
    bool ok = true;
    QObject::connect(&socket, &QTcpSocket::connected, [&socket, &ok]() {
        std::cout << "connected successed" << std::endl;
        new std::thread([&socket, &ok]() {
            // while (ok) {
            // static int c = 0;
            // std::cout << "send a data cnt " << c++ << std::endl;
            // QDataStream out{&socket};
            // out << std::rand();
            // socket.flush();
            //}
            QDataStream out{&socket};
            for (int i = 0; i < 6; i++) {
                out << target0[i];
            }
            socket.flush();
        });
    });
    QObject::connect(&socket, &QTcpSocket::disconnected, [&ok]() {
        std::cout << "out line" << std::endl;
        ok = false;
    });
    QObject::connect(&socket, &QTcpSocket::readyRead, [&]() {
        auto bytes = socket.readAll();
        URData data{bytes};
        for (int i = 0; i < 6; i++) {
            data.Tool_vector_actual[i] =
                reverse_value(data.Tool_vector_actual[i]);
            printf("%3.6f ", data.Tool_vector_actual[i]);
        }
        printf("error: %3.6f ", calc_error(target0, data));
        std::cout << std::endl;
    });

    socket.connectToHost("127.0.0.1", 30003);

    return app.exec();
}
