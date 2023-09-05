#ifndef MY_VIEW_H
#define MY_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <QRubberBand>
#include <QMouseEvent>
#include <QDebug>

class My_view : public QGraphicsView
{
    Q_OBJECT
public:
    My_view();
    My_view(QWidget *parent) : QGraphicsView(parent) {}
    QPointF left_up = QPointF(0.0, 0.0), right_down = QPointF(1.0, 1.0);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    signals:
    void justZoomedIn();
public slots:
private:
    QRubberBand *band = new QRubberBand(QRubberBand::Rectangle, this);;
    QPoint start, end;
    bool band_select = false;
    QPointF absolutiseCoords(QPointF left_up, QPointF right_down, QPointF p);
    QPointF relativiseCoords(QPointF left_up, QPointF right_down, QPointF p);
};

#endif // MY_VIEW_H
