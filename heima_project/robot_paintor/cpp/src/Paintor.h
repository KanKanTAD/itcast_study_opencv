#pragma once

#include <qevent.h>
#include <qpoint.h>
#include <qwidget.h>

#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QWidget>
#include <atomic>
#include <cmath>
#include <memory>
#include <vector>

struct point2d_t {
    float x, y;

    point2d_t(int x, int y) : x{(float)x}, y{(float)y} {
    }
    point2d_t(float x, float y) : x{x}, y{y} {
    }
    point2d_t() : point2d_t(0.f, 0.f) {
    }

    int int_x() {
        return int(std::roundf(x));
    }
    int int_y() {
        return int(std::roundf(y));
    }

    QPoint to_qpoint() {
        return QPoint(int_x(), int_y());
    }
};

class Paintor : public QWidget {
    Q_OBJECT
      public:
    Paintor(QWidget* ptr = nullptr);
    virtual ~Paintor() {
    }

    void clear_pts() {
        muti_pts.clear();
        this->update();
    }

    std::shared_ptr<std::vector<std::vector<point2d_t>>> load_muti_pts(
        int sample_step = 3);

      protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

      private:
    std::vector<std::vector<point2d_t>> muti_pts;

    std::atomic_bool is_mouse_press{false};
};
