#include <qhostaddress.h>
#include <qobject.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <chrono>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

std::list<QTcpSocket*> socket_s;

void on_server_connect() {
}
void on_server_disconnect() {
}
void on_server_ready_read() {
	QObject::s
}
void on_server_bytes_written(qint64 data) {
}

int main(int argc, char** argv) {
    QCoreApplication app{argc, argv};

    QTcpServer server{};
    server.listen(QHostAddress::Any, 30003);
    std::cout << "server listen in 0.0.0.0 : 30003" << std::endl;

    QObject::connect(&server, &QTcpServer::newConnection, [&]() mutable {
        auto socket = server.nextPendingConnection();
        socket_s.push_back(socket);
        auto s = QString("[%1:%2] -- successed connected")
                     .arg(socket->peerAddress().toString())
                     .arg(socket->peerPort());
        std::cout << s.toStdString() << std::endl;
        QObject::connect(socket, &QTcpSocket::connected, on_server_connect);
        QObject::connect(
            socket, &QTcpSocket::disconnected, on_server_disconnect);
        QObject::connect(socket, &QTcpSocket::readyRead, on_server_ready_read);
        QObject::connect(
            socket, &QTcpSocket::bytesWritten, on_server_bytes_written);
    });

    new std::thread([&]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(120));
            for (auto s : socket_s) {
                s->write("hi");
            }
        }
    });
    return app.exec();
}
