#ifndef MY_SCENE_H
#define MY_SCENE_H


#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPainter>
#include <QRubberBand>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class My_scene : public QGraphicsScene
{
    //Q_OBJECT
    //Q_INTERFACES(QGraphicsScene)
public:
    My_scene();
    QPointF left_up = QPointF(0.0, 0.0), right_down = QPointF(1.0, 1.0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    signals:
    void justZoomedIn();
public slots:
private:
    QRubberBand *band;
    QPoint start, end;
    bool band_select = false;
    QPointF absolutiseCoords(QPointF left_up, QPointF right_down, QPointF p);
};


#endif // MY_SCENE_H
