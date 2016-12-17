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
    mainLayout->addWidget(paintArea, 1, 1);

    upToolBar = new QToolBar;
    loadButton = new QPushButton(tr("&Load"));
    loadButton->setToolTip(tr("Load picture from a file"));
    upToolBar->addWidget(loadButton);
    connect(loadButton, SIGNAL(clicked()), paintArea, SLOT(
                loadFromFile()));

    saveButton = new QPushButton(tr("&Save"));
    saveButton->setToolTip(tr("Save picture to a file"));
    upToolBar->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), paintArea, SLOT(
                saveToFile()));

    penButton = new QPushButton(tr("&Pen"));
    penButton->setCheckable(true);
    upToolBar->addWidget(penButton);
    brushButton = new QPushButton(tr("&Brush"));
    upToolBar->addWidget(brushButton);
    textButton = new QPushButton(tr("&Text"));
    upToolBar->addWidget(textButton);
    rubberButton = new QPushButton(tr("&Rubber"));
    upToolBar->addWidget(rubberButton);
    dropperButton = new QPushButton(tr("&Dropper"));
    upToolBar->addWidget(dropperButton);
    canButton = new QPushButton(tr("&Can"));
    upToolBar->addWidget(canButton);

    mainLayout->addWidget(upToolBar, 0, 0, 1, 3);

    leftToolBar = new QToolBar;
    leftToolBar->setOrientation(Qt::Vertical);

    lineSelBtn = new QPushButton(tr("&Line"));
    leftToolBar->addWidget(lineSelBtn);
    circleSelBtn = new QPushButton(tr("&Circle"));
    leftToolBar->addWidget(circleSelBtn);
    rectSelBtn = new QPushButton(tr("&Rect"));
    leftToolBar->addWidget(rectSelBtn);
    elipseSelBtn = new QPushButton(tr("&Elipse"));
    leftToolBar->addWidget(elipseSelBtn);
    curveSelBtn = new QPushButton(tr("&Curve"));
    leftToolBar->addWidget(curveSelBtn);

    mainLayout->addWidget(leftToolBar, 1, 0);

    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::keyPressEvent(QKeyEvent *event)
//{
//    if(event->key() == Qt::Key_A){
//        color = QColor(Qt::blue);
//    }
//    else{
//        color = QColor(Qt::red);
//    }
//}


