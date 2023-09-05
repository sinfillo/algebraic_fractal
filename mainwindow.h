#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include "my_view.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;
    QGraphicsScene *frac_scene = new QGraphicsScene();
    My_view *frac_view;
public slots:
    void drawFractal();
private:
    QPointF absolutiseCoords(QPointF left_up, QPointF right_down, QPointF p);

};
#endif // MAINWINDOW_H
