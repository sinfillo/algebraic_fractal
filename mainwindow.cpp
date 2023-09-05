#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "complex.h"
int IT = 300;
double EPS = 1e-6;
double L = 200;

int get_point(complex point, complex z_point) {
    int ind = 0;
    complex one(1, 0);
    complex two(2, 0);
    //qDebug() << point.get_a() << " " << point.get_b();
    for (ind = 0; ind < IT; ++ind) {
        z_point = (z_point * z_point) + point;
        if (ind <= 2) {
            //qDebug() << z_point.get_a() << " " << z_point.get_b();
        }
        if (z_point.module() > 2.0 + EPS) {
            break;
        }
    }

    return ind;
}

//QPoint start, end;
std::vector<QColor> colors;
QPointF MainWindow::absolutiseCoords(QPointF left_up, QPointF right_down, QPointF p) {
    return QPointF(p.x() * (right_down.x() - left_up.x()) + left_up.x(),
                  p.y() * (right_down.y() - left_up.y()) + left_up.y());
}
void MainWindow::drawFractal() {
    QPointF absolute_left_up = {-2.0, -2.0}, absolute_right_down = {2.0, 2.0};
    QPointF cur_left_up = absolutiseCoords(absolute_left_up, absolute_right_down, frac_view->left_up);
    QPointF cur_right_down = absolutiseCoords(absolute_left_up, absolute_right_down, frac_view->right_down);
    QImage fractal_img(frac_view->width(), frac_view->height(), QImage::Format_RGB32);
    for (int x_pix = 0; x_pix < frac_view->width(); ++x_pix) {
        for (int y_pix = 0; y_pix < frac_view->height(); ++y_pix) {
            QPointF p(static_cast<double>(x_pix) / frac_view->width(), static_cast<double>(y_pix) / frac_view->height());
            p = absolutiseCoords(cur_left_up, cur_right_down, p);
            p.setY(-p.y());
            complex z(p.x(), p.y());
            complex z_point(0, 0);
            int cur_it = get_point(z, z_point);
            fractal_img.setPixelColor(x_pix, y_pix, colors[cur_it].toRgb());
        }
    }
    frac_scene->clear();
    frac_scene->addPixmap(QPixmap::fromImage(fractal_img));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    frac_view = new My_view(this);
    frac_view->setGeometry(20, 20, 513, 513);
    frac_view->setScene(frac_scene);
    colors.resize(IT + 1);
    int ind_j = 0;
    for (int ind_i = 0; ind_i <= IT; ++ind_i) {
        if (ind_j < 359) {
            colors[ind_i] = QColor::fromHsl(ind_j, 210, 150).name();
        } else {
            colors[ind_i] = colors[ind_i - 1];
        }
        ind_j += 3;
    }
    drawFractal();
    connect(frac_view, &My_view::justZoomedIn, this, &MainWindow::drawFractal);
}


MainWindow::~MainWindow()
{
    delete ui;
}

