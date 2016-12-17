#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

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

    PaintArea *paintArea;

    QToolBar *upToolBar;
    QPushButton *setStyleBtn;
    QPushButton *setBrushBtn;
    QPushButton *setWidthBtn;
    QPushButton *setColorBtn;
    QPushButton *textBtn;

    QToolBar * setWidthToolBar;
    QPushButton *width_1_Btn;
    QPushButton *width_2_Btn;
    QPushButton *width_3_Btn;
    QPushButton *width_4_Btn;
    QPushButton *width_5_Btn;
    QPushButton *width_6_Btn;
    QPushButton *width_7_Btn;
    QPushButton *width_8_Btn;

    QToolBar * setStyleToolBar;
    QPushButton *style_SolidLine_Btn;
    QPushButton *style_DashLine_Btn;
    QPushButton *style_DotLine_Btn;
    QPushButton *style_DashDotLine_Btn;
    QPushButton *style_DashDotDotLine_Btn;
    QPushButton *style_CustomDashLine_Btn;

    QToolBar *leftToolBar;
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

    QButtonGroup *settingToolBoxButtonGroup;

    void uncheckAllToolBar();
    void createSettingToolBox();

public slots:
    void lineSelBtnSlot();
    void circleSelBtnSlot();
    void rectSelBtnSlot();
    void ellipseSelBtnSlot();
    void curveSelBtnSlot();

    void penSelBtnSlot();
    void brushSelBtnSlot();
    void textSelBtnSlot();
    void rubberSelBtnSlot();
    void dropperSelBtnSlot();
    void canSelBtnSlot();

    void selectBtnSlot(PaintArea::PaintType type);
    void buttonGroupClicked(int id);
};

#endif // MAINWINDOW_H
