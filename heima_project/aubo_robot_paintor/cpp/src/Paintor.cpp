#include "Paintor.h"

#include <qcolor.h>
#include <qpainter.h>
#include <qpen.h>

#include <QVBoxLayout>
#include <iostream>
#include <memory>
#include <vector>

Paintor::Paintor(QWidget* ptr) : QWidget(ptr) {
    this->setAutoFillBackground(true);
    this->setStyleSheet("background-color:white;");
    this->show();
}

std::shared_ptr<std::vector<std::vector<point2d_t>>> Paintor::load_muti_pts(
    int sample_step) {
    auto* ptr = new std::vector<std::vector<point2d_t>>{};

    for (auto& pts : this->muti_pts) {
        ptr->push_back(std::vector<point2d_t>{});
        for (int i = 0; i < pts.size(); i += sample_step) {
            ptr->back().push_back(pts.at(i));
        }
    }

    return std::shared_ptr<std::vector<std::vector<point2d_t>>>{ptr};
}

void Paintor::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter{this};
    QPen pen;
    pen.setColor(QColor{255, 0, 0});
    painter.setPen(pen);

    for (std::vector<point2d_t>& pts : this->muti_pts) {
        for (int i = 1; i < pts.size(); ++i) {
            auto& prev_pt = pts.at(i - 1);
            auto& pt      = pts.at(i);

            painter.drawLine(QPoint{prev_pt.int_x(), prev_pt.int_y()},
                             QPoint{pt.int_x(), pt.int_y()});
        }
    }
}

void Paintor::mousePressEvent(QMouseEvent* event) {
    if (!can_mouse) {
        return;
    }
    this->is_mouse_press = true;
    this->muti_pts.push_back(std::vector<point2d_t>{});
    this->muti_pts.back().push_back({event->x(), event->y()});
}
void Paintor::mouseMoveEvent(QMouseEvent* event) {
    if (this->is_mouse_press == false) {
        return;
    }
    // std::cout << event->x() << "," << event->y() << std::endl;
    this->muti_pts.back().push_back({event->x(), event->y()});
    this->update();
}
void Paintor::mouseReleaseEvent(QMouseEvent* event) {
    if (!can_mouse) {
        return;
    }
    this->is_mouse_press = false;
}
