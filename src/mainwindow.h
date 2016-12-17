#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include <QDebug>

#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
#include <QToolBar>

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
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *penButton;
    QPushButton *brushButton;
    QPushButton *textButton;
    QPushButton *rubberButton;
    QPushButton *dropperButton;
    QPushButton *canButton;

    QToolBar *leftToolBar;
    QPushButton *lineSelBtn;
    QPushButton *circleSelBtn;
    QPushButton *rectSelBtn;
    QPushButton *ellipseSelBtn;
    QPushButton *curveSelBtn;

    void uncheckAllLeftToolBar();

public slots:
    void lineSelBtnSlot();
    void circleSelBtnSlot();
    void rectSelBtnSlot();
    void ellipseSelBtnSlot();
    void curveSelBtnSlot();
};

#endif // MAINWINDOW_H
