
#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <chrono>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

#include "ur_sim_server.h"

int main(int argc, char** argv) {
    QCoreApplication app{argc, argv};

    ur_sim::get_instance();

    return app.exec();
}
