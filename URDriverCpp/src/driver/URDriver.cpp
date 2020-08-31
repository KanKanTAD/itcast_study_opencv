
#include "URDriver.h"

#include <qabstractsocket.h>

URDriver::URDriver() {
    QObject::connect(&this->socket, &QTcpSocket::connected, [this]() {
        this->connect_callback_func();
    });

    QObject::connect(&this->socket, &QTcpSocket::disconnected, [this]() {
        this->disconnect_callback_func();
    });
}

void URDriver::connectToRobot(QString ip, int port) {
    socket.connectToHost(ip, port);
}

void URDriver::disconnetToRobot() {
    socket.disconnectFromHost();
}

void URDriver::eval_by_qstring(const QString& script) {
    socket.write(script.toUtf8().data());
}
