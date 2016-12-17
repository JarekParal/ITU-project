#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>

#include <QDebug>

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QPainter>
#include <QPicture>
#include <QImage>
#include <QImageWriter>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QGuiApplication>
#include <QRect>
#include <QPaintEvent>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum class Type { line, rect, circle };
    void paintObject(PaintArea::Type type, int x1, int y1, int x2, int y2);


signals:

public slots:
    void loadFromFile();
    void saveToFile();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QPainter *painter;
    QPainterPath painterPath;
    QPixmap pixmap;
    QPixmap* image;

    int paintActivate;
};

#endif // PAINTAREA_H
