#include "ur_sim_server.h"

#include <qhostaddress.h>
#include <qobject.h>
#include <qtcpsocket.h>

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <mutex>

ur_sim::ur_sim() {
    memset(target, 0, sizeof(target));
    memset(state.Tool_vector_actual, 0, sizeof(state.Tool_vector_actual));
    server.listen(QHostAddress::Any, 30003);
    std::cout << "server have be listen at 0.0.0.0:30003" << std::endl;

    QObject::connect(&this->server, &QTcpServer::newConnection, [this]() {
        auto socket = this->server.nextPendingConnection();
        this->socket_s.push_back(socket);

        auto s = QString("[%1:%2] -- successed connected")
                     .arg(socket->peerAddress().toString())
                     .arg(socket->peerPort());
        std::cout << s.toStdString() << std::endl;

        QObject::connect(
            socket, SIGNAL(connected()), this, SLOT(on_server_connect()));
        QObject::connect(
            socket, SIGNAL(disconnected()), this, SLOT(on_server_disconnect()));
        QObject::connect(
            socket, SIGNAL(readyRead()), this, SLOT(on_server_ready_read()));
    });

    QObject::connect(
        &this->timer, SIGNAL(timeout()), this, SLOT(on_time_out()));
    // timer.setInterval(120);
    timer.start(120);
}

void ur_sim::on_server_connect() {
}
void ur_sim::on_server_disconnect() {
    std::lock_guard<std::mutex> _guard{socket_s_mut};
    auto socket = dynamic_cast<QTcpSocket*>(QObject::sender());
    socket_s.remove(socket);
}
void ur_sim::on_server_ready_read() {
    std::cout << "got it" << std::endl;
    auto socket = dynamic_cast<QTcpSocket*>(QObject::sender());
    auto data   = socket->readAll();
    memcpy(target, data.data(), sizeof(target));
    for (auto& t : target) {
        t = reverse_value(t);
        std::cout << t << " ,";
    }
    std::cout << std::endl;
}
void ur_sim::on_server_bytes_written(quint64 data) {
}

void ur_sim::on_time_out() {
    double step = 0.001;
    for (int i = 0; i < 6; i++) {
        auto c = target[i] - state.Tool_vector_actual[i];
        state.Tool_vector_actual[i] += c > 0 ? step : c < 0 ? -step : 0;
    }
    {
        std::lock_guard<std::mutex> _guard{socket_s_mut};
        QByteArray data;
        int i = 0;
        for (auto socket : socket_s) {
            socket->write(state.toQByteArray(data));
        }
    }
}

double ur_sim::calc_error() {
    double res = 0.0;
    for (int i = 0; i < 6; i++) {
        res += std::pow(target[i] - state.Tool_vector_actual[i], 2);
    }
    res /= 6.0;
    return res;
}
