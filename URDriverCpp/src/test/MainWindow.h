#pragma once

#include <qboxlayout.h>
#include <qlineedit.h>

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextLine>
#include <QVBoxLayout>
#include <QWidget>
#include <string>
#include <vector>

#include "URDriver.h"

struct tool_interface {
    virtual std::string get_ip() = 0;
    virtual int get_port()       = 0;
};

static const char* movel_lab_names[] = {"x:", "y:", "z:", "rx:", "ry:", "rz:"};

class MainWindow : public QWidget, public tool_interface {
    Q_OBJECT
      private:
    bool is_connected = false;
    QVBoxLayout main_layer{this};
    QLineEdit ip_edit;
    QLineEdit port_edit{"30003"};

    QLabel connect_state{"have no connected"};

    QPushButton connect_btn{"connect"};
    QPushButton disconnect_btn{"disconnect"};

    const int joint_cnt = {6};
    QLineEdit joint_edits[6];

    QPushButton movej_btn{"moevj"};

    const int movel_lab_cnt = {6};
    QLineEdit movel_edits[6];

    QPushButton movel_btn{"movel"};

      public:
    MainWindow(QWidget* ptr = nullptr);

    virtual std::string get_ip() override;
    virtual int get_port() override;

      private:
    void init_interface();
    void init_event();

      public slots:
    void connect_to_robot();
    void disconnect_from_robot();
    void movej();
    void movel();
};
