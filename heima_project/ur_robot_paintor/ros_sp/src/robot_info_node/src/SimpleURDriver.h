#pragma once

#include <QAbstractSocket>
#include <QObject>
#include <QTcpSocket>
#include <atomic>
#include <functional>
#include <memory>
#include <string>

#include "UR_Data.hpp"

class SimpleURDriver : public QObject {
    Q_OBJECT

    QTcpSocket socket;
    std::atomic_bool is_connected{false};

      public:
    using Ptr_t = std::shared_ptr<SimpleURDriver>;

    std::function<void()> on_connected_func;
    std::function<void()> on_disconnected_func;
    std::function<void()> on_readyread_func;
    std::function<void(QAbstractSocket::SocketError)> on_error_func;

    URData ur_data;
    std::string host{"127.0.0.1"};
    int port = 30003;

    SimpleURDriver(const std::string& host, int port);
    SimpleURDriver() : SimpleURDriver("127.0.0.1", 30003) {
    }

    virtual ~SimpleURDriver() {
        qInfo() << "release SimpleURDriver " << this;
    }

    void _connect_to_host() {
        on_connect_to_host();
    }

      signals:
    void connect_to_host();
    void disconnect_from_host();

    void print(const std::string&);

      protected slots:
    void on_print(const std::string&);
    void on_connect_to_host();
    void on_disconnect_from_host();
    void on_connected();
    void on_disconnected();
    void on_readyread();
    void on_error(QAbstractSocket::SocketError);
};
