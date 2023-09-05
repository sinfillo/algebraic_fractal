#include "my_scene.h"

My_scene::My_scene() {
    band = new QRubberBand(QRubberBand::Rectangle);
}

void My_scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    start = event->scenePos().toPoint();
    qDebug() << start;
    band_select = true;
    return;
}


void My_scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (band_select) {
        band->setGeometry(QRect(start, event->scenePos().toPoint()).normalized());
        band->show();
        if (event->pos().x() < 0 || event->pos().x() >= width()) {
            return;
        }
        if (event->pos().y() < 0 || event->pos().y() >= height()) {
            return;
        }
        end = event->scenePos().toPoint();
    }
    return;
}

QPointF My_scene::absolutiseCoords(QPointF left_up, QPointF right_down, QPointF p) {
    return QPointF(p.x() * (right_down.x() - left_up.x()) + left_up.x(),
                  p.y() * (right_down.y() - left_up.y()) + left_up.y());
}

void My_scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    band_select = false;
    band->hide();
    if (!(event->pos().x() < 0 || event->pos().x() >= width() ||
          event->pos().y() < 0 || event->pos().y() >= height())) {
        end = event->scenePos().toPoint();
    }
    qDebug() << start << " : " << end;
    int del_x, del_y;
    del_x = std::abs(end.x() - start.x()), del_y = std::abs(end.y() - start.y());
    if (del_x > 0 && del_y > 0) {
        QPointF cur_left_up(static_cast<double>(std::min(start.x(), end.x())) / width(),
                             static_cast<double>(std::min(start.y(), end.y())) / height());
        QPointF cur_right_down(static_cast<double>(std::max(start.x(), end.x())) / width(),
                              static_cast<double>(std::max(start.y(), end.y())) / height());
        cur_left_up = absolutiseCoords(left_up, right_down, cur_left_up);
        cur_right_down = absolutiseCoords(left_up, right_down, cur_right_down);
        left_up = cur_left_up, right_down = cur_right_down;
        emit justZoomedIn();
    }

    return;
}

void My_scene::justZoomedIn() {}

