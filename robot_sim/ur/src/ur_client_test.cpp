#include <qcoreapplication.h>
#include <qobject.h>
#include <qtcpsocket.h>

#include <QCoreApplication>
#include <QTcpSocket>
#include <iostream>

int main(int argc, char** argv) {
    QCoreApplication app{argc, argv};
    QTcpSocket socket;
    QObject::connect(&socket, &QTcpSocket::connected, []() {
        std::cout << "connected successed" << std::endl;
    });
    QObject::connect(&socket, &QTcpSocket::disconnected, []() {
        std::cout << "out line" << std::endl;
    });
    QObject::connect(&socket, &QTcpSocket::readyRead, [&]() {
        auto bytes = socket.readAll();
        std::cout << bytes.data() << std::endl;
    });
    socket.connectToHost("127.0.0.1", 30003);
    return app.exec();
}
