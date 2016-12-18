#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QResource>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGuiApplication::setApplicationDisplayName("ITU-project Paint");

    QResource::registerResource("icon.qrc");

    //Q_INIT_RESOURCE(resources);

    paintArea = new PaintArea;
    scrollArea.setWidget(paintArea);

    mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    //mainLayout->addWidget(&scrollArea, 1, 1);

    upToolBar = new QToolBar;
    upToolBar->setOrientation(Qt::Horizontal);
    createUpToolBar();
    upToolBar->setMovable(false);

    setStyleBar = new QToolBar;
    setStyleBar->setOrientation(Qt::Vertical);
    createStyleBar();

    setWidthBar = new QToolBar;
    setWidthBar->setOrientation(Qt::Vertical);
    createWidthBar();

    setColorBar = new QToolBar;
    setColorBar->setOrientation(Qt::Vertical);
    createColorBar();

    leftToolBar = new QToolBar;
    leftToolBar->setOrientation(Qt::Vertical);
    createToolBar();

    //// Old style of layouting - MainWindow : QWidget
    //rightToolLayout = new QHBoxLayout;
    //mainLayout->addLayout(rightToolLayout, 1, 2);

    //mainLayout->addWidget(upToolBar, 0, 0, 1, 3);

    //mainLayout->addWidget(setStyleBar, 1, 2);
    //rightToolLayout->addWidget(setStyleBar);

    //mainLayout->addWidget(setWidthBar, 1, 3);
    //rightToolLayout->addWidget(setWidthBar);

    //mainLayout->addWidget(setColorBar, 1, 4);
    //rightToolLayout->addWidget(setColorBar);

    //mainLayout->addWidget(leftToolBar, 1, 0);
    //setLayout(mainLayout);


    //// New style of layouting - MainWindow : QMainWindow
    setCentralWidget(&scrollArea);

    addToolBar(upToolBar);

    addToolBar(Qt::RightToolBarArea, setColorBar);
    addToolBarBreak(Qt::RightToolBarArea);
    addToolBar(Qt::RightToolBarArea, setStyleBar);
    addToolBarBreak(Qt::RightToolBarArea);
    addToolBar(Qt::RightToolBarArea, setWidthBar);

    addToolBar(Qt::LeftToolBarArea, leftToolBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::upToolBarButtonGroupClicked(int id)
{
    switch (static_cast<SettingBar>(id)) {
        case SettingBar::style:
            if(setStyleBar->isHidden())
                setStyleBar->show();
            else
                setStyleBar->hide();
            break;

        case SettingBar::width:
            if(setWidthBar->isHidden())
                setWidthBar->show();
            else
                setWidthBar->hide();
            break;

        case SettingBar::color:
            if(setColorBar->isHidden()) {
                setColorBar->show();
            } else {
                setColorBar->hide();
            }
            break;

//        case SettingBar::style:
//            if(setStyleBar->isHidden())
//                setStyleBar->show();
//            else
//                setStyleBar->hide();
//            break;

        default:
            break;
    }
}

void MainWindow::styleBarButtonGroupClicked(int id)
{
    Qt::PenStyle type = static_cast<Qt::PenStyle>(id);
    paintArea->actualPenStyle = type;

    setButtonGroupChecked(styleBarButtonGroup, id);
}

void MainWindow::widthBarButtonGroupClicked(int id)
{
    paintArea->actualPenWidth = id;

    setButtonGroupChecked(widthBarButtonGroup, id);
}

void MainWindow::colorBarButtonGroupClicked(int id)
{
//    qDebug() << "color - id: " << id << "  "
//             << "string: " << QColor::colorNames().at(id);

//    for(auto color : QColor::colorNames()) {
//        qDebug() << color;
//    }

//    foreach (QString name, QColor::colorNames())
//       qDebug() << name;

    QColor type = defaultColor.at(id);
    paintArea->actualPenColor = type;

    setButtonGroupChecked(colorBarButtonGroup, id);
}

void MainWindow::toolBarButtonGroupClicked(int id)
{
    qDebug() << "selectBtnSlot: " << static_cast<int>(id);

    PaintArea::PaintType type = static_cast<PaintArea::PaintType>(id);
    paintArea->actualPaintType=type;

    setButtonGroupChecked(toolBarButtonGroup, id);
}

void MainWindow::createUpToolBar()
{
    upToolBarButtonGroup = new QButtonGroup(this);
    upToolBarButtonGroup->setExclusive(false);

    connect(upToolBarButtonGroup, SIGNAL(buttonClicked(int)),
           this, SLOT(upToolBarButtonGroupClicked(int)));

    const int upToolBarButtonSizeX = 100;
    const int upToolBarButtonSizeY = 60;

    const int btnIconSizeX = 60;
    const int btnIconSizeY = 50;
    const int btnIconSizeStartEndX = 5;

    QPixmap buttonIcon = QPixmap(btnIconSizeX, btnIconSizeY);
    buttonIcon.fill(Qt::white);

    QPainter paint;
    paint.begin(&buttonIcon);
    paint.setPen(QPen(Qt::black, 5));
    paint.drawLine(btnIconSizeStartEndX, btnIconSizeY/2,
                   btnIconSizeX - btnIconSizeStartEndX, btnIconSizeY/2);
    paint.end();

    QPushButton * newButton = new QPushButton(tr("&New"));
    newButton->setToolTip(tr("New picture"));
    upToolBar->addWidget(newButton);
    connect(newButton, SIGNAL(clicked()), paintArea, SLOT(initImage()));
    newButton->setMinimumSize(upToolBarButtonSizeX,upToolBarButtonSizeY);

    loadButton = new QPushButton(tr("&Load"));
    loadButton->setToolTip(tr("Load picture from a file"));
    upToolBar->addWidget(loadButton);
    connect(loadButton, SIGNAL(clicked()), paintArea, SLOT(
                loadFromFile()));
    loadButton->setMinimumSize(upToolBarButtonSizeX,upToolBarButtonSizeY);

    saveButton = new QPushButton(tr("&Save"));
    saveButton->setToolTip(tr("Save picture to a file"));
    upToolBar->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), paintArea, SLOT(
                saveToFile()));
    saveButton->setMinimumSize(upToolBarButtonSizeX,upToolBarButtonSizeY);

    QPushButton *setStyleBtn = new QPushButton(tr("&Style"));
    setStyleBtn->setCheckable(true);
    setStyleBtn->setIcon(QIcon(":/icon/resource/qpen-solid.png"));
    setStyleBtn->setIconSize(QSize(60,40));
    upToolBarButtonGroup->
            addButton(setStyleBtn, static_cast<int>(SettingBar::style));
    upToolBar->addWidget(setStyleBtn);

//    QPushButton *setBrushBtn = new QPushButton(tr("&Brush"));
//    setBrushBtn->setCheckable(true);
//    upToolBarButtonGroup->
//            addButton(setBrushBtn, static_cast<int>(SettingBar::brush));
//    upToolBar->addWidget(setBrushBtn);

    QPushButton *setWidthBtn = new QPushButton(tr("&Width"));
    setWidthBtn->setCheckable(true);
    setWidthBtn->setIcon(buttonIcon);
    setWidthBtn->setIconSize(buttonIcon.size());
    upToolBarButtonGroup->
            addButton(setWidthBtn, static_cast<int>(SettingBar::width));
    upToolBar->addWidget(setWidthBtn);

    buttonIcon.fill(Qt::white);
    paint.begin(&buttonIcon);
    paint.setPen(QPen(Qt::red, 5));
    paint.setBrush(Qt::red);
    paint.drawRect(0, 0, btnIconSizeX/2, btnIconSizeY/2);
    paint.setPen(QPen(Qt::blue, 5));
    paint.setBrush(Qt::blue);
    paint.drawRect(btnIconSizeX/2, btnIconSizeY/2, btnIconSizeX, btnIconSizeY);
    paint.setPen(QPen(Qt::green, 5));
    paint.setBrush(Qt::green);
    paint.drawRect(0, btnIconSizeY/2, btnIconSizeX/2, btnIconSizeY);
    paint.end();

    QPushButton *setColorBtn = new QPushButton(tr("&Color"));
    setColorBtn->setCheckable(true);
    setColorBtn->setIcon(buttonIcon);
    setColorBtn->setIconSize(buttonIcon.size());
    upToolBarButtonGroup->
            addButton(setColorBtn, static_cast<int>(SettingBar::color));
    upToolBar->addWidget(setColorBtn);

    QList<QAbstractButton *> buttons = upToolBarButtonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        button->setChecked(true);
        button->setMinimumSize(upToolBarButtonSizeX,upToolBarButtonSizeY);
    }
}

void MainWindow::createStyleBar()
{
    styleBarButtonGroup = new QButtonGroup(this);
    styleBarButtonGroup->setExclusive(false);

    connect(styleBarButtonGroup, SIGNAL(buttonClicked(int)),
           this, SLOT(styleBarButtonGroupClicked(int)));

    QPushButton *style_SolidLine_Btn = new QPushButton(tr("&SolidLine"));
    style_SolidLine_Btn->setCheckable(true);
    style_SolidLine_Btn->setIcon(QIcon(":/icon/resource/qpen-solid.png"));
    styleBarButtonGroup->
            addButton(style_SolidLine_Btn, static_cast<int>(Qt::SolidLine));
    setStyleBar->addWidget(style_SolidLine_Btn);

    QPushButton *style_DashLine_Btn = new QPushButton(tr("&DashLine"));
    style_DashLine_Btn->setCheckable(true);
    style_DashLine_Btn->setIcon(QIcon(":/icon/resource/qpen-dash.png"));
    styleBarButtonGroup->
            addButton(style_DashLine_Btn, static_cast<int>(Qt::DashLine));
    setStyleBar->addWidget(style_DashLine_Btn);

    QPushButton *style_DotLine_Btn = new QPushButton(tr("&DotLine"));
    style_DotLine_Btn->setCheckable(true);
    style_DotLine_Btn->setIcon(QIcon(":/icon/resource/qpen-dot.png"));
    styleBarButtonGroup->
            addButton(style_DotLine_Btn, static_cast<int>(Qt::DotLine));
    setStyleBar->addWidget(style_DotLine_Btn);

    QPushButton *style_DashDotLine_Btn = new QPushButton(tr("&DashDotLine"));
    style_DashDotLine_Btn->setCheckable(true);
    style_DashDotLine_Btn->setIcon(QIcon(":/icon/resource/qpen-dashdot.png"));
    styleBarButtonGroup->
            addButton(style_DashDotLine_Btn, static_cast<int>(Qt::DashDotLine));
    setStyleBar->addWidget(style_DashDotLine_Btn);

    QPushButton *style_DashDotDotLine_Btn = new QPushButton(tr("&DashDotDotLine"));
    style_DashDotDotLine_Btn->setCheckable(true);
    style_DashDotDotLine_Btn->setIcon(QIcon(":/icon/resource/qpen-dashdotdot.png"));
    styleBarButtonGroup->
            addButton(style_DashDotDotLine_Btn, static_cast<int>(Qt::DashDotDotLine));
    setStyleBar->addWidget(style_DashDotDotLine_Btn);

//    QPushButton *style_CustomDashLine_Btn = new QPushButton(tr("&CustomDashLine"));
//    style_CustomDashLine_Btn->setCheckable(true);
 //   style_CustomDashLine_Btn->setIcon(QIcon(":/icon/resource/qpen-custom.png"));
//    styleBarButtonGroup->
//            addButton(style_CustomDashLine_Btn, static_cast<int>(Qt::CustomDashLine));
//    setStylelBar->addWidget(style_CustomDashLine_Btn);

    QList<QAbstractButton *> buttons = styleBarButtonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        button->setMinimumSize(100,100);
        button->setIconSize(QSize(80,80));
        button->setText("");
    }
}

void MainWindow::createWidthBar()
{
    widthBarButtonGroup = new QButtonGroup(this);
    widthBarButtonGroup->setExclusive(false);

    connect(widthBarButtonGroup, SIGNAL(buttonClicked(int)),
           this, SLOT(widthBarButtonGroupClicked(int)));

    const int widthBtnCount = 20;
    QPushButton *widthBtn[widthBtnCount];
    const int startingWidth = 1;
    int arrayPos = startingWidth;

    for(int i = startingWidth; i <= widthBtnCount; ++i) {
        arrayPos = i - startingWidth;
        widthBtn[arrayPos] = new QPushButton(QString::number(i));
        widthBtn[arrayPos]->setCheckable(true);

        const int btnIconSizeX = 40;
        const int btnIconSizeY = 40;
        const int btnIconSizeStartEndX = 5;

        QPixmap buttonIcon = QPixmap(btnIconSizeX, btnIconSizeY);
        buttonIcon.fill(Qt::white);

        QPainter paint;
        paint.begin(&buttonIcon);
        paint.setPen(QPen(Qt::black, i));
        paint.drawLine(btnIconSizeStartEndX, btnIconSizeY/2,
                       btnIconSizeX - btnIconSizeStartEndX, btnIconSizeY/2);
        paint.end();

        widthBtn[arrayPos]->setIcon(buttonIcon);
        widthBtn[arrayPos]->setIconSize(buttonIcon.size());

        widthBarButtonGroup->
                addButton(widthBtn[arrayPos], i);
        setWidthBar->addWidget(widthBtn[arrayPos]);
    }
}

void MainWindow::createColorBar()
{
    colorBarButtonGroup = new QButtonGroup(this);
    colorBarButtonGroup->setExclusive(false);

    connect(colorBarButtonGroup, SIGNAL(buttonClicked(int)),
           this, SLOT(colorBarButtonGroupClicked(int)));

    const int colorBtnCount = defaultColor.size();
    QToolButton *colorBtn[colorBtnCount];
    const int startingColor = 0;
    int arrayPos = startingColor;

    for(int i = startingColor; i < colorBtnCount; ++i) {
        arrayPos = i - startingColor;

        colorBtn[arrayPos] = new QToolButton();
        colorBtn[arrayPos]->setCheckable(true);

//        colorBtn[arrayPos]->setPalette(QPalette(defaultColor.at(i)));
//        colorBtn[arrayPos]->setAutoFillBackground(true);

        colorBtn[arrayPos]->setMinimumSize(60,60);
        QPixmap buttonIcon = QPixmap(80, 80);
        buttonIcon.fill(defaultColor.at(i));
        colorBtn[arrayPos]->setIcon(buttonIcon);
        colorBtn[arrayPos]->setIconSize(buttonIcon.size());

        colorBarButtonGroup->
                addButton(colorBtn[arrayPos], i);
        setColorBar->addWidget(colorBtn[arrayPos]);
    }
}


void MainWindow::createToolBar()
{
    toolBarButtonGroup = new QButtonGroup(this);
    toolBarButtonGroup->setExclusive(false);

    connect(toolBarButtonGroup, SIGNAL(buttonClicked(int)),
           this, SLOT(toolBarButtonGroupClicked(int)));

    penButton = new QPushButton(tr("&Pen"));
    penButton->setCheckable(true);
    penButton->setChecked(true);
    toolBarButtonGroup->
            addButton(penButton, static_cast<int>(PaintArea::PaintType::pen));
    leftToolBar->addWidget(penButton);

//    brushButton = new QPushButton(tr("&Brush"));
//    brushButton->setCheckable(true);
//    toolBarButtonGroup->
//            addButton(brushButton, static_cast<int>(PaintArea::PaintType::brush));
//    leftToolBar->addWidget(brushButton);

//    textButton = new QPushButton(tr("&Text"));
//    textButton->setCheckable(true);
//    toolBarButtonGroup->
//            addButton(textButton, static_cast<int>(PaintArea::PaintType::text));
//    leftToolBar->addWidget(textButton);

    rubberButton = new QPushButton(tr("&Rubber"));
    rubberButton->setCheckable(true);
    toolBarButtonGroup->
            addButton(rubberButton, static_cast<int>(PaintArea::PaintType::rubber));
    leftToolBar->addWidget(rubberButton);

//    dropperButton = new QPushButton(tr("&Dropper"));
//    dropperButton->setCheckable(true);
//    toolBarButtonGroup->
//            addButton(dropperButton, static_cast<int>(PaintArea::PaintType::dropper));
//    leftToolBar->addWidget(dropperButton);

//    canButton = new QPushButton(tr("&Can"));
//    canButton->setCheckable(true);
//    toolBarButtonGroup->
//            addButton(canButton, static_cast<int>(PaintArea::PaintType::can));
//    leftToolBar->addWidget(canButton);

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

//    curveSelBtn = new QPushButton(tr("&Curve"));
//    curveSelBtn->setCheckable(true);
//    toolBarButtonGroup->
//            addButton(curveSelBtn, static_cast<int>(PaintArea::PaintType::curve));
//    leftToolBar->addWidget(curveSelBtn);

    QList<QAbstractButton *> buttons = toolBarButtonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        button->setMinimumSize(100,100);
    }
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


