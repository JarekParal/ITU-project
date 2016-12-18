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
#include <QButtonGroup>

#include "paintArea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QScrollArea scrollArea;
    PaintArea *paintArea;

    QToolBar *upToolBar;
    QPushButton *setStyleBtn;
    QPushButton *setBrushBtn;
    QPushButton *setWidthBtn;
    QPushButton *setColorBtn;
    QPushButton *textBtn;

    QToolBar * setWidthBar;

    QButtonGroup *widthBarButtonGroup;
    void createWidthBar();

    QToolBar * setStyleBar;

    QButtonGroup *styleBarButtonGroup;
    void createStyleBar();

    QPushButton *style_SolidLine_Btn;
    QPushButton *style_DashLine_Btn;
    QPushButton *style_DotLine_Btn;
    QPushButton *style_DashDotLine_Btn;
    QPushButton *style_DashDotDotLine_Btn;
    QPushButton *style_CustomDashLine_Btn;

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
    void toolBarButtonGroupClicked(int id);
    void styleBarButtonGroupClicked(int id);
    void widthBarButtonGroupClicked(int id);
};

#endif // MAINWINDOW_H
