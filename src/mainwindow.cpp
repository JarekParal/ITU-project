#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    color = QColor(Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    points.append(event->pos());

    this->update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    points.append(event->pos());

    this->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    points.append(event->pos());

    this->update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(QColor(color));
    painter.drawPolyline(points.data(), points.count());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A){
        color = QColor(Qt::blue);
    }
    else{
        color = QColor(Qt::red);
    }
}


