#include "SimpleURDriver.h"

#include <qobject.h>

#include <QDebug>
#include <string>

SimpleURDriver::SimpleURDriver(const std::string& host, int port)
    : host{host}, port{port} {
    qRegisterMetaType<std::string>("std::string");

    QObject::connect(this,
                     SIGNAL(print(const std::string&)),
                     this,
                     SLOT(on_print(const std::string&)));

    QObject::connect(&socket, SIGNAL(connected()), this, SLOT(on_connected()));

    QObject::connect(
        &socket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));

    QObject::connect(&socket, SIGNAL(readyRead()), this, SLOT(on_readyread()));

    QObject::connect(&socket,
                     SIGNAL(error(QAbstractSocket::SocketError)),
                     this,
                     SLOT(on_error(QAbstractSocket::SocketError)));
    QObject::connect(
        this, SIGNAL(connect_to_host()), this, SLOT(on_connect_to_host()));

    QObject::connect(this,
                     SIGNAL(disconnect_from_host()),
                     this,
                     SLOT(on_disconnect_from_host()));
}

void SimpleURDriver::on_connected() {
    qInfo() << "be connected from <-- " << tr(host.c_str()) << ":" << port;
    is_connected = true;
    this->on_connected_func();
}
void SimpleURDriver::on_disconnected() {
    qInfo() << "disconnect_from_host <-- " << tr(host.c_str()) << ":" << port;
    is_connected = false;
    this->on_disconnected_func();
}
void SimpleURDriver::on_readyread() {
    auto bytes = socket.readAll();
    URData::set_by_qbytearray(this->ur_data, bytes);
    this->on_readyread_func();
}
void SimpleURDriver::on_error(QAbstractSocket::SocketError code) {
    qInfo() << "error from <-- " << tr(host.c_str()) << ":" << port << " ;by "
            << code;
    is_connected = false;
    this->on_error_func(code);
}

void SimpleURDriver::on_connect_to_host() {
    qInfo() << "connect to ->" << tr(host.c_str()) << ":" << port;
    socket.connectToHost(QString::fromStdString(this->host), port);
}
void SimpleURDriver::on_disconnect_from_host() {
    socket.disconnectFromHost();
}
void SimpleURDriver::on_print(const std::string& s) {
    socket.write(QString::fromStdString(s).toUtf8());
    socket.flush();
}
