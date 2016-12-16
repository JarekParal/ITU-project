#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)//, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);

    paintArea = new PaintArea;

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(paintArea, 1, 0);
    setLayout(mainLayout);

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

//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event);
//    QPainter painter(this);
//
//    painter.setPen(QColor(color));
//    painter.drawPolyline(points.data(), points.count());
//}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A){
        color = QColor(Qt::blue);
    }
    else{
        color = QColor(Qt::red);
    }
}


