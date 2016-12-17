#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)//, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);

    paintArea = new PaintArea;

    loadButton = new QPushButton(tr("&Load"));
    loadButton->setToolTip(tr("Load contacts from a file"));
//    saveButton = new QPushButton(tr("&Save"));
//    saveButton->setToolTip(tr("Save contacts to a file"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(paintArea, 1, 0);
    mainLayout->addWidget(loadButton, 0, 0);
//    mainLayout->addWidget(saveButton, 0, 1);
    setLayout(mainLayout);

    connect(loadButton, SIGNAL(clicked()), paintArea, SLOT(
                loadFromFile()));
//    connect(saveButton, SIGNAL(clicked()), paintArea, SLOT(
//                saveToFile()));

    color = QColor(Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //points.append(event->pos());
    x = event->x();
    y = event->y();

    this->update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //points.append(event->pos());

    paintArea->paintObject(paintArea->Type::line, x, y, event->x(), event->y());

    this->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //points.append(event->pos());

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


