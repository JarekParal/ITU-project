#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include <QDebug>

#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>

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
    QPushButton * loadButton;
    QPushButton * saveButton;
};

#endif // MAINWINDOW_H
