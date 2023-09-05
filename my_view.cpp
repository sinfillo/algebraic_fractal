#include "my_view.h"

My_view::My_view() {
}

void My_view::mousePressEvent(QMouseEvent *event) {
    start = event->pos();
    band_select = true;
    return;
}


void My_view::mouseMoveEvent(QMouseEvent *event) {
    if (band_select) {
        band->setGeometry(QRect(start, event->pos()).normalized());
        band->show();
        if (event->pos().x() < 0 || event->pos().x() >= width()) {
            return;
        }
        if (event->pos().y() < 0 || event->pos().y() >= height()) {
            return;
        }
        end = event->pos();
    }
    return;
}

QPointF My_view::absolutiseCoords(QPointF left_up, QPointF right_down, QPointF p) {
    return QPointF(p.x() * (right_down.x() - left_up.x()) + left_up.x(),
                  p.y() * (right_down.y() - left_up.y()) + left_up.y());
}
QPointF My_view::relativiseCoords(QPointF left_up, QPointF right_down, QPointF p) {
    return QPointF((p.x() - left_up.x()) / (right_down.x() - left_up.x()),
                   (p.y() - left_up.y()) / (right_down.y() - left_up.y()));
}

void My_view::mouseReleaseEvent(QMouseEvent *event) {
    band_select = false;
    band->hide();
    if (!(event->pos().x() < 0 || event->pos().x() >= width() ||
          event->pos().y() < 0 || event->pos().y() >= height())) {
        end = event->pos();
    }
//    qDebug() << start << " : " << end;
    int del_x, del_y;
    del_x = end.x() - start.x(), del_y = std::abs(end.y() - start.y());
    if (del_x > 0 && del_y > 0) {
        del_x = std::abs(del_x);
        QPointF cur_left_up(static_cast<double>(std::min(start.x(), end.x())) / width(),
                             static_cast<double>(std::min(start.y(), end.y())) / height());
        QPointF cur_right_down(static_cast<double>(std::max(start.x(), end.x())) / width(),
                              static_cast<double>(std::max(start.y(), end.y())) / height());
        cur_left_up = absolutiseCoords(left_up, right_down, cur_left_up);
        cur_right_down = absolutiseCoords(left_up, right_down, cur_right_down);
        left_up = cur_left_up, right_down = cur_right_down;
        emit justZoomedIn();
    } else if (del_x < 0 && del_y > 0) {
        del_x = std::abs(del_x);
        QPointF cur_left_up(static_cast<double>(std::min(start.x(), end.x())) / width(),
                             static_cast<double>(std::min(start.y(), end.y())) / height());
        QPointF cur_right_down(static_cast<double>(std::max(start.x(), end.x())) / width(),
                              static_cast<double>(std::max(start.y(), end.y())) / height());
        cur_left_up = absolutiseCoords(left_up, right_down, cur_left_up);
        cur_right_down = absolutiseCoords(left_up, right_down, cur_right_down);
        QPointF rel_left_up = relativiseCoords(cur_left_up, cur_right_down, left_up);
        QPointF rel_right_down = relativiseCoords(cur_left_up, cur_right_down, right_down);
        cur_left_up = absolutiseCoords(left_up, right_down, rel_left_up);
        cur_right_down = absolutiseCoords(left_up, right_down, rel_right_down);
        left_up = cur_left_up, right_down = cur_right_down;
        emit justZoomedIn();
    }

    return;
}

//void My_view::justZoomedIn() {}

