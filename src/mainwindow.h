#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QScrollArea>

#include <QDebug>

#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
#include <QToolBar>
#include <QToolButton>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QColor>

#include "paintArea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow //QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout *mainLayout;

    QScrollArea scrollArea;
    PaintArea *paintArea;

    QHBoxLayout *rightToolLayout;
    QToolBar *upToolBar;
    QButtonGroup *upToolBarButtonGroup;
    void createUpToolBar();

    enum class SettingBar { style, brush, width, color};

    QPushButton *setStyleBtn;
    QPushButton *setBrushBtn;
    QPushButton *setWidthBtn;
    QPushButton *setColorBtn;
    QPushButton *textBtn;

    QToolBar * setStyleBar;
    QButtonGroup *styleBarButtonGroup;
    void createStyleBar();

    QToolBar * setWidthBar;
    QButtonGroup *widthBarButtonGroup;
    void createWidthBar();

    QToolBar * setColorBar;
    QButtonGroup *colorBarButtonGroup;
    void createColorBar();

    QVector <QColor> defaultColor
        = {Qt::white, Qt::black, Qt::red, Qt::green,
           Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow,
           Qt::gray};


    QToolBar *leftToolBar;
    QButtonGroup *toolBarButtonGroup;
    void createToolBar();

    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *penButton;
    QPushButton *brushButton;
    QPushButton *textButton;
    QPushButton *rubberButton;
    QPushButton *dropperButton;
    QPushButton *canButton;

    QPushButton *lineSelBtn;
    QPushButton *circleSelBtn;
    QPushButton *rectSelBtn;
    QPushButton *ellipseSelBtn;
    QPushButton *curveSelBtn;

    void setButtonGroupChecked(QButtonGroup * buttonGroup, int id);


public slots:
    void upToolBarButtonGroupClicked(int id);
    void toolBarButtonGroupClicked(int id);
    void styleBarButtonGroupClicked(int id);
    void widthBarButtonGroupClicked(int id);
    void colorBarButtonGroupClicked(int id);
};

#endif // MAINWINDOW_H
