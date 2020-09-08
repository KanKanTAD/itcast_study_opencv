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
#include <string>
#include <vector>

struct point2d_t {
    double x, y;

    point2d_t(int x, int y) : x{(float)x}, y{(float)y} {
    }
    point2d_t(double x, double y) : x{x}, y{y} {
    }
    point2d_t() : point2d_t(0.f, 0.f) {
    }

    std::string str() const {
        return "{ x:" + std::to_string(x) + ", y:" + std::to_string(y) + " }";
    }

    int int_x() const {
        return int(std::roundf(x));
    }
    int int_y() const {
        return int(std::roundf(y));
    }

    QPoint to_qpoint() {
        return QPoint(int_x(), int_y());
    }

    void normalize(const point2d_t& mi, const point2d_t& mx) {
        auto delta_x = mx.x - mi.x;
        auto delta_y = mx.y - mi.y;
        x            = (x - mi.x) / delta_x;
        y            = (y - mi.y) / delta_y;
    }

    static void min_max(std::vector<point2d_t>& pts,
                        double& min_x,
                        double& min_y,
                        double& max_x,
                        double& max_y) {
    }

    static void normalize(std::vector<point2d_t>& pts,
                          const point2d_t& mi,
                          const point2d_t& mx) {
        for (auto& pt : pts) {
            pt.normalize(mi, mx);
        }
    }

    static void normalize(std::vector<std::vector<point2d_t>>& ptss) {
    }
};

class Paintor : public QWidget {
    Q_OBJECT
      public:
    bool can_mouse = true;
    Paintor(QWidget* ptr = nullptr);
    virtual ~Paintor() {
    }

    void clear_pts() {
        muti_pts.clear();
        this->update();
    }

    std::shared_ptr<std::vector<std::vector<point2d_t>>> load_muti_pts(
        int sample_step = 3);

    void set_pts_s(std::vector<std::vector<point2d_t>>& muti_pts) {
        this->muti_pts = muti_pts;
    }

      protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

      private:
    std::vector<std::vector<point2d_t>> muti_pts;

    std::atomic_bool is_mouse_press{false};
};
