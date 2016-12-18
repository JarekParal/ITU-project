#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)//, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);

    QGuiApplication::setApplicationDisplayName("ITU-project Paint");

    paintArea = new PaintArea;

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(paintArea, 1, 1);

    leftToolBar = new QToolBar;
    leftToolBar->setOrientation(Qt::Vertical);

    upToolBar = new QToolBar;

    mainLayout->addWidget(upToolBar, 0, 0, 1, 3);

    createToolsBox();
    mainLayout->addWidget(leftToolBar, 1, 0);

    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toolsBoxButtonGroupClicked(int id)
{
    qDebug() << "selectBtnSlot: " << static_cast<int>(id);

    PaintArea::PaintType type = static_cast<PaintArea::PaintType>(id);
    paintArea->actualPaintType=type;

    QList<QAbstractButton *> buttons = toolsBoxButtonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (toolsBoxButtonGroup->button(id) != button)
            button->setChecked(false);
        else
            button->setChecked(true);
    }
}

void MainWindow::createToolsBox()
{
    toolsBoxButtonGroup = new QButtonGroup(this);
    toolsBoxButtonGroup->setExclusive(false);

    connect(toolsBoxButtonGroup, SIGNAL(buttonClicked(int)),
           this, SLOT(toolsBoxButtonGroupClicked(int)));

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
    toolsBoxButtonGroup->
            addButton(penButton, static_cast<int>(PaintArea::PaintType::pen));
    leftToolBar->addWidget(penButton);

    brushButton = new QPushButton(tr("&Brush"));
    brushButton->setCheckable(true);
    toolsBoxButtonGroup->
            addButton(brushButton, static_cast<int>(PaintArea::PaintType::brush));
    leftToolBar->addWidget(brushButton);

    textButton = new QPushButton(tr("&Text"));
    textButton->setCheckable(true);
    toolsBoxButtonGroup->
            addButton(textButton, static_cast<int>(PaintArea::PaintType::text));
    leftToolBar->addWidget(textButton);

    rubberButton = new QPushButton(tr("&Rubber"));
    rubberButton->setCheckable(true);
    toolsBoxButtonGroup->
            addButton(rubberButton, static_cast<int>(PaintArea::PaintType::rubber));
    leftToolBar->addWidget(rubberButton);

    dropperButton = new QPushButton(tr("&Dropper"));
    dropperButton->setCheckable(true);
    toolsBoxButtonGroup->
            addButton(dropperButton, static_cast<int>(PaintArea::PaintType::dropper));
    leftToolBar->addWidget(dropperButton);

    canButton = new QPushButton(tr("&Can"));
    canButton->setCheckable(true);
    toolsBoxButtonGroup->
            addButton(canButton, static_cast<int>(PaintArea::PaintType::can));
    leftToolBar->addWidget(canButton);

    lineSelBtn = new QPushButton(tr("&Line"));
    lineSelBtn->setCheckable(true);
    lineSelBtn->setIconSize(QSize(50,50));
    toolsBoxButtonGroup->
            addButton(lineSelBtn, static_cast<int>(PaintArea::PaintType::line));
    leftToolBar->addWidget(lineSelBtn);

    circleSelBtn = new QPushButton(tr("&Circle"));
    circleSelBtn->setCheckable(true);
    toolsBoxButtonGroup->
            addButton(circleSelBtn, static_cast<int>(PaintArea::PaintType::circle));
    leftToolBar->addWidget(circleSelBtn);

    rectSelBtn = new QPushButton(tr("&Rect"));
    rectSelBtn->setCheckable(true);
    toolsBoxButtonGroup->
            addButton(rectSelBtn, static_cast<int>(PaintArea::PaintType::rect));
    leftToolBar->addWidget(rectSelBtn);

    ellipseSelBtn = new QPushButton(tr("&Ellipse"));
    ellipseSelBtn->setCheckable(true);
    toolsBoxButtonGroup->
            addButton(ellipseSelBtn, static_cast<int>(PaintArea::PaintType::ellipse));
    leftToolBar->addWidget(ellipseSelBtn);

    curveSelBtn = new QPushButton(tr("&Curve"));
    curveSelBtn->setCheckable(true);
    toolsBoxButtonGroup->
            addButton(curveSelBtn, static_cast<int>(PaintArea::PaintType::curve));
    leftToolBar->addWidget(curveSelBtn);
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


