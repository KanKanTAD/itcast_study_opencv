#pragma once

#include <qpushbutton.h>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "Paintor.h"

class MainWindow : public QWidget {
    Q_OBJECT
      public:
    MainWindow(QWidget* ptr = nullptr);
    virtual ~MainWindow() {
    }

      private:
    QGridLayout main_layout{this};
    QLineEdit ip_edit;
    QLineEdit port_edit;

    QLabel state_label;

    QPushButton connect_btn{"connect"};
    QPushButton disconnect_btn{"disconnect"};

    Paintor paintor;

    QPushButton paint_btn{"paint"};
    QPushButton clean_btn{"clean"};
};
