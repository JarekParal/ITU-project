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
    createToolBar();
    mainLayout->addWidget(leftToolBar, 1, 0);

    setStylelBar = new QToolBar;
    setStylelBar->setOrientation(Qt::Vertical);
    createStyleBar();
    mainLayout->addWidget(setStylelBar, 1, 2);

    upToolBar = new QToolBar;
    mainLayout->addWidget(upToolBar, 0, 0, 1, 3);


    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toolBarButtonGroupClicked(int id)
{
    qDebug() << "selectBtnSlot: " << static_cast<int>(id);

    PaintArea::PaintType type = static_cast<PaintArea::PaintType>(id);
    paintArea->actualPaintType=type;

    setButtonGroupChecked(toolBarButtonGroup, id);
}

void MainWindow::styleBarButtonGroupClicked(int id)
{
    Qt::PenStyle type = static_cast<Qt::PenStyle>(id);
    paintArea->actualPenStyle = type;

    setButtonGroupChecked(styleBarButtonGroup, id);
}


void MainWindow::createStyleBar()
{
    styleBarButtonGroup = new QButtonGroup(this);
    styleBarButtonGroup->setExclusive(false);

    connect(styleBarButtonGroup, SIGNAL(buttonClicked(int)),
           this, SLOT(styleBarButtonGroupClicked(int)));

    QPushButton *style_SolidLine_Btn = new QPushButton(tr("&SolidLine"));
    style_SolidLine_Btn->setCheckable(true);
    styleBarButtonGroup->
            addButton(style_SolidLine_Btn, static_cast<int>(Qt::SolidLine));
    setStylelBar->addWidget(style_SolidLine_Btn);

    QPushButton *style_DashLine_Btn = new QPushButton(tr("&DashLine"));
    style_DashLine_Btn->setCheckable(true);
    styleBarButtonGroup->
            addButton(style_DashLine_Btn, static_cast<int>(Qt::DashLine));
    setStylelBar->addWidget(style_DashLine_Btn);

    QPushButton *style_DotLine_Btn = new QPushButton(tr("&Load"));
    QPushButton *style_DashDotLine_Btn = new QPushButton(tr("&Load"));
    QPushButton *style_DashDotDotLine_Btn = new QPushButton(tr("&Load"));
    QPushButton *style_CustomDashLine_Btn = new QPushButton(tr("&Load"));
}


void MainWindow::createToolBar()
{
    toolBarButtonGroup = new QButtonGroup(this);
    toolBarButtonGroup->setExclusive(false);

    connect(toolBarButtonGroup, SIGNAL(buttonClicked(int)),
           this, SLOT(toolBarButtonGroupClicked(int)));

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
    toolBarButtonGroup->
            addButton(penButton, static_cast<int>(PaintArea::PaintType::pen));
    leftToolBar->addWidget(penButton);

    brushButton = new QPushButton(tr("&Brush"));
    brushButton->setCheckable(true);
    toolBarButtonGroup->
            addButton(brushButton, static_cast<int>(PaintArea::PaintType::brush));
    leftToolBar->addWidget(brushButton);

    textButton = new QPushButton(tr("&Text"));
    textButton->setCheckable(true);
    toolBarButtonGroup->
            addButton(textButton, static_cast<int>(PaintArea::PaintType::text));
    leftToolBar->addWidget(textButton);

    rubberButton = new QPushButton(tr("&Rubber"));
    rubberButton->setCheckable(true);
    toolBarButtonGroup->
            addButton(rubberButton, static_cast<int>(PaintArea::PaintType::rubber));
    leftToolBar->addWidget(rubberButton);

    dropperButton = new QPushButton(tr("&Dropper"));
    dropperButton->setCheckable(true);
    toolBarButtonGroup->
            addButton(dropperButton, static_cast<int>(PaintArea::PaintType::dropper));
    leftToolBar->addWidget(dropperButton);

    canButton = new QPushButton(tr("&Can"));
    canButton->setCheckable(true);
    toolBarButtonGroup->
            addButton(canButton, static_cast<int>(PaintArea::PaintType::can));
    leftToolBar->addWidget(canButton);

    lineSelBtn = new QPushButton(tr("&Line"));
    lineSelBtn->setCheckable(true);
    lineSelBtn->setIconSize(QSize(50,50));
    toolBarButtonGroup->
            addButton(lineSelBtn, static_cast<int>(PaintArea::PaintType::line));
    leftToolBar->addWidget(lineSelBtn);

    circleSelBtn = new QPushButton(tr("&Circle"));
    circleSelBtn->setCheckable(true);
    toolBarButtonGroup->
            addButton(circleSelBtn, static_cast<int>(PaintArea::PaintType::circle));
    leftToolBar->addWidget(circleSelBtn);

    rectSelBtn = new QPushButton(tr("&Rect"));
    rectSelBtn->setCheckable(true);
    toolBarButtonGroup->
            addButton(rectSelBtn, static_cast<int>(PaintArea::PaintType::rect));
    leftToolBar->addWidget(rectSelBtn);

    ellipseSelBtn = new QPushButton(tr("&Ellipse"));
    ellipseSelBtn->setCheckable(true);
    toolBarButtonGroup->
            addButton(ellipseSelBtn, static_cast<int>(PaintArea::PaintType::ellipse));
    leftToolBar->addWidget(ellipseSelBtn);

    curveSelBtn = new QPushButton(tr("&Curve"));
    curveSelBtn->setCheckable(true);
    toolBarButtonGroup->
            addButton(curveSelBtn, static_cast<int>(PaintArea::PaintType::curve));
    leftToolBar->addWidget(curveSelBtn);
}

void MainWindow::setButtonGroupChecked(QButtonGroup *buttonGroup, int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
        else
            button->setChecked(true);
    }
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


