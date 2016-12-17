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

    mainLayout->addWidget(upToolBar, 0, 0, 1, 3);

    createSettingToolBox();
    mainLayout->addWidget(leftToolBar, 1, 0);

    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonGroupClicked(int id)
{
    qDebug() << "selectBtnSlot: " << static_cast<int>(id);

    PaintArea::PaintType type = static_cast<PaintArea::PaintType>(id);
    paintArea->actualPaintType=type;

    QList<QAbstractButton *> buttons = settingToolBoxButtonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (settingToolBoxButtonGroup->button(id) != button)
            button->setChecked(false);
        else
            button->setChecked(true);
    }
}

void MainWindow::createSettingToolBox()
{
    settingToolBoxButtonGroup = new QButtonGroup(this);
    settingToolBoxButtonGroup->setExclusive(false);

    connect(settingToolBoxButtonGroup, SIGNAL(buttonClicked(int)),
           this, SLOT(buttonGroupClicked(int)));

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
    settingToolBoxButtonGroup->
            addButton(penButton, static_cast<int>(PaintArea::PaintType::pen));
    leftToolBar->addWidget(penButton);

    brushButton = new QPushButton(tr("&Brush"));
    brushButton->setCheckable(true);
    settingToolBoxButtonGroup->
            addButton(brushButton, static_cast<int>(PaintArea::PaintType::brush));
    leftToolBar->addWidget(brushButton);

    textButton = new QPushButton(tr("&Text"));
    textButton->setCheckable(true);
    settingToolBoxButtonGroup->
            addButton(textButton, static_cast<int>(PaintArea::PaintType::text));
    leftToolBar->addWidget(textButton);

    rubberButton = new QPushButton(tr("&Rubber"));
    rubberButton->setCheckable(true);
    settingToolBoxButtonGroup->
            addButton(rubberButton, static_cast<int>(PaintArea::PaintType::rubber));
    leftToolBar->addWidget(rubberButton);

    dropperButton = new QPushButton(tr("&Dropper"));
    dropperButton->setCheckable(true);
    settingToolBoxButtonGroup->
            addButton(dropperButton, static_cast<int>(PaintArea::PaintType::dropper));
    leftToolBar->addWidget(dropperButton);

    canButton = new QPushButton(tr("&Can"));
    canButton->setCheckable(true);
    settingToolBoxButtonGroup->
            addButton(canButton, static_cast<int>(PaintArea::PaintType::can));
    leftToolBar->addWidget(canButton);

    lineSelBtn = new QPushButton(tr("&Line"));
    lineSelBtn->setCheckable(true);
    lineSelBtn->setIconSize(QSize(50,50));
    settingToolBoxButtonGroup->
            addButton(lineSelBtn, static_cast<int>(PaintArea::PaintType::line));
    leftToolBar->addWidget(lineSelBtn);

    circleSelBtn = new QPushButton(tr("&Circle"));
    circleSelBtn->setCheckable(true);
    settingToolBoxButtonGroup->
            addButton(circleSelBtn, static_cast<int>(PaintArea::PaintType::circle));
    leftToolBar->addWidget(circleSelBtn);

    rectSelBtn = new QPushButton(tr("&Rect"));
    rectSelBtn->setCheckable(true);
    settingToolBoxButtonGroup->
            addButton(rectSelBtn, static_cast<int>(PaintArea::PaintType::rect));
    leftToolBar->addWidget(rectSelBtn);

    ellipseSelBtn = new QPushButton(tr("&Ellipse"));
    ellipseSelBtn->setCheckable(true);
    settingToolBoxButtonGroup->
            addButton(ellipseSelBtn, static_cast<int>(PaintArea::PaintType::ellipse));
    leftToolBar->addWidget(ellipseSelBtn);

    curveSelBtn = new QPushButton(tr("&Curve"));
    curveSelBtn->setCheckable(true);
    settingToolBoxButtonGroup->
            addButton(curveSelBtn, static_cast<int>(PaintArea::PaintType::curve));
    leftToolBar->addWidget(curveSelBtn);
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


