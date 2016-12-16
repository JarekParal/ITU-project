#include "paintArea.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
//    painter = new QPainter(this);

    pixmap.load(":/images/qt-logo.png");
//    painter->drawPixmap(0,0,pixmap);

}

QSize PaintArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize PaintArea::sizeHint() const
{
    return QSize(400, 200);
}

void PaintArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter paint(this);

    paint.drawPixmap(0,0,pixmap);

    paint.setPen(QColor(Qt::blue));
    paint.drawLine(0,0,100,100);
}
