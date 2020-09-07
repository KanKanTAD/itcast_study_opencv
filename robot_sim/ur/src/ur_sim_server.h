#pragma once

#include <qtcpserver.h>
#include <qtcpsocket.h>

#include <QCoreApplication>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

#include "UR_Data.hpp"
class ur_sim : public QObject {
    Q_OBJECT

    ur_sim();

    ur_sim(const ur_sim&) = delete;
    ur_sim& operator=(const ur_sim&) = delete;

    QTcpServer server{this};
    std::list<QTcpSocket*> socket_s;

    std::mutex socket_s_mut;

    QTimer timer{this};

    URData state;

    const double epsilon = 0.001;
    double target[6];

    double calc_error();

      protected:
    virtual ~ur_sim() {
        server.close();
    }

      public:
    static ur_sim& get_instance() {
        static ur_sim instance;
        return instance;
    }

    template <typename T>
    static T reverse_value(T v) {
        std::uint8_t data[sizeof(T)];
        memcpy(data, &v, sizeof(T));
        std::reverse(std::begin(data), std::end(data));
        return *((T*)(data));
    }

      protected slots:
    void on_server_connect();
    void on_server_disconnect();
    void on_server_ready_read();
    void on_server_bytes_written(quint64);

    void on_time_out();
};
