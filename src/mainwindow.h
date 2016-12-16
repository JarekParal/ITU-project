#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

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

    QVector <QPointF> points;

    QColor color;

private:
    Ui::MainWindow *ui;

    PaintArea *paintArea;
    QPushButton * loadButton;
    QPushButton * saveButton;

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
