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

    leftToolBar = new QToolBar;
    leftToolBar->setOrientation(Qt::Vertical);

    upToolBar = new QToolBar;

    loadButton = new QPushButton(tr("&Load"));
    loadButton->setToolTip(tr("Load picture from a file"));
    leftToolBar->addWidget(loadButton);
    connect(loadButton, SIGNAL(clicked()), paintArea, SLOT(
                loadFromFile()));

    saveButton = new QPushButton(tr("&Save"));
    saveButton->setToolTip(tr("Save picture to a file"));
    leftToolBar->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), paintArea, SLOT(
                saveToFile()));

    penButton = new QPushButton(tr("&Pen"));
    penButton->setCheckable(true);
    connect(penButton, SIGNAL(clicked()),
            this, SLOT(penSelBtnSlot()));
    leftToolBar->addWidget(penButton);
    brushButton = new QPushButton(tr("&Brush"));
    brushButton->setCheckable(true);
    connect(brushButton, SIGNAL(clicked()),
            this, SLOT(brushSelBtnSlot()));
    leftToolBar->addWidget(brushButton);
    textButton = new QPushButton(tr("&Text"));
    textButton->setCheckable(true);
    connect(textButton, SIGNAL(clicked()),
            this, SLOT(textSelBtnSlot()));
    leftToolBar->addWidget(textButton);
    rubberButton = new QPushButton(tr("&Rubber"));
    rubberButton->setCheckable(true);
    connect(rubberButton, SIGNAL(clicked()),
            this, SLOT(rubberSelBtnSlot()));
    leftToolBar->addWidget(rubberButton);
    dropperButton = new QPushButton(tr("&Dropper"));
    dropperButton->setCheckable(true);
    connect(dropperButton, SIGNAL(clicked()),
            this, SLOT(dropperSelBtnSlot()));
    leftToolBar->addWidget(dropperButton);
    canButton = new QPushButton(tr("&Can"));
    canButton->setCheckable(true);
    connect(canButton, SIGNAL(clicked()),
            this, SLOT(canSelBtnSlot()));
    leftToolBar->addWidget(canButton);

    mainLayout->addWidget(upToolBar, 0, 0, 1, 3);

    lineSelBtn = new QPushButton(tr("&Line"));
    lineSelBtn->setCheckable(true);
    leftToolBar->addWidget(lineSelBtn);
    connect(lineSelBtn, SIGNAL(clicked()),
            this, SLOT(selectBtnSlot(PaintArea::PaintType::line)));

    circleSelBtn = new QPushButton(tr("&Circle"));
    circleSelBtn->setCheckable(true);
    leftToolBar->addWidget(circleSelBtn);
    connect(circleSelBtn, SIGNAL(clicked()),
            this, SLOT(circleSelBtnSlot()));
    rectSelBtn = new QPushButton(tr("&Rect"));
    rectSelBtn->setCheckable(true);
    leftToolBar->addWidget(rectSelBtn);
    connect(rectSelBtn, SIGNAL(clicked()),
            this, SLOT(rectSelBtnSlot()));
    ellipseSelBtn = new QPushButton(tr("&Elipse"));
    ellipseSelBtn->setCheckable(true);
    leftToolBar->addWidget(ellipseSelBtn);
    connect(ellipseSelBtn, SIGNAL(clicked()),
            this, SLOT(ellipseSelBtnSlot()));
    curveSelBtn = new QPushButton(tr("&Curve"));
    curveSelBtn->setCheckable(true);
    leftToolBar->addWidget(curveSelBtn);
    connect(curveSelBtn, SIGNAL(clicked()),
            this, SLOT(curveSelBtnSlot()));

    mainLayout->addWidget(leftToolBar, 1, 0);

    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::selectBtnSlot(PaintArea::PaintType type)
{
    qDebug() << "selectBtnSlot: " << static_cast<int>(type);

    if(type == PaintArea::PaintType::line)
    {
        lineSelBtn->setChecked(true);
        paintArea->actualPaintType=PaintArea::PaintType::line;
    }
}

void MainWindow::uncheckAllToolBar()
{
    lineSelBtn->setChecked(false);
    circleSelBtn->setChecked(false);
    rectSelBtn->setChecked(false);
    ellipseSelBtn->setChecked(false);
    curveSelBtn->setChecked(false);

    penButton->setChecked(false);
    brushButton->setChecked(false);
    textButton->setChecked(false);
    rubberButton->setChecked(false);
    dropperButton->setChecked(false);
    canButton->setChecked(false);
}

void MainWindow::lineSelBtnSlot()
{
    uncheckAllToolBar();

    qDebug() << "lineSelBtnSlot: " << static_cast<int>(paintArea->actualPaintType) << "\n";
}

void MainWindow::circleSelBtnSlot()
{
    uncheckAllToolBar();
    circleSelBtn->setChecked(true);
    paintArea->actualPaintType=paintArea->PaintType::circle;

    qDebug() << "circleSelBtnSlot: " << static_cast<int>(paintArea->actualPaintType) << "\n";
}

void MainWindow::rectSelBtnSlot()
{
    uncheckAllToolBar();
    rectSelBtn->setChecked(true);
    paintArea->actualPaintType=paintArea->PaintType::rect;

    qDebug() << "circleSelBtnSlot: " << static_cast<int>(paintArea->actualPaintType) << "\n";
}

void MainWindow::ellipseSelBtnSlot()
{
    uncheckAllToolBar();
    ellipseSelBtn->setChecked(true);
    paintArea->actualPaintType=paintArea->PaintType::ellipse;
}

void MainWindow::curveSelBtnSlot()
{
    uncheckAllToolBar();
    curveSelBtn->setChecked(true);
    paintArea->actualPaintType=paintArea->PaintType::curve;
}




void MainWindow::penSelBtnSlot()
{
    uncheckAllToolBar();
    penButton->setChecked(true);
    paintArea->actualPaintType=paintArea->PaintType::pen;
}

void MainWindow::brushSelBtnSlot()
{
    uncheckAllToolBar();
    brushButton->setChecked(true);
    paintArea->actualPaintType=paintArea->PaintType::brush;
}

void MainWindow::textSelBtnSlot()
{
    uncheckAllToolBar();
    textButton->setChecked(true);
    paintArea->actualPaintType=paintArea->PaintType::text;
}

void MainWindow::rubberSelBtnSlot()
{
    uncheckAllToolBar();
    rubberButton->setChecked(true);
    paintArea->actualPaintType=paintArea->PaintType::rubber;
}

void MainWindow::dropperSelBtnSlot()
{
    uncheckAllToolBar();
    dropperButton->setChecked(true);
    paintArea->actualPaintType=paintArea->PaintType::dropper;
}

void MainWindow::canSelBtnSlot()
{
    uncheckAllToolBar();
    canButton->setChecked(true);
    paintArea->actualPaintType=paintArea->PaintType::can;
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


