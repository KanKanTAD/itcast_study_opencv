#pragma once

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
    int paintor_width  = 500;
    int paintor_height = 400;

    QGridLayout main_layout{this};
    QLineEdit ip_edit;
    QLineEdit port_edit;

    QLabel state_label;

    QPushButton connect_btn{"connect"};
    QPushButton disconnect_btn{"disconnect"};

    QLineEdit origin_edit;
    QLineEdit x_axes_edit;
    QLineEdit y_axes_edit;
    QLineEdit rx_ry_rz;

    Paintor paintor;

    QPushButton paint_btn{"paint"};
    QPushButton stop_btn{"stop"};
    QPushButton preview_btn{"preview"};
    QPushButton clean_btn{"clean"};

    QLineEdit pose_edits[6];
    QLabel pose_labels[6];

    QLineEdit pt_step_edit;

    QLineEdit a_edit;
    QLineEdit v_edit;
    QLineEdit epsilon_edit;

    QPushButton test_movel_btn{"test move line"};

      protected slots:
    void do_paint();
};
