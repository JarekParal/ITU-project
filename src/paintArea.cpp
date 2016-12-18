#include "paintArea.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    //To allow paint events outside of paintEvent
    //setAttribute(Qt::WA_StaticContents);

    actualPaintType = PaintType::line;
    actualPenStyle = Qt::SolidLine;
    actualPenWidth = 1;
    actualPenColor = Qt::black;

    initImage();

    paintActivate = true;
}


void PaintArea::initImage()
{
    image = new QPixmap(800, 800);
    image->fill(Qt::white);
    this->update();
}

QSize PaintArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize PaintArea::sizeHint() const
{
    return image->size();
}

void PaintArea::paintEvent(QPaintEvent * event)
{
    if(paintActivate == true) {
        QPainter painter(this);
        QRect rec = event->rect();
        painter.drawPixmap(rec, *image, rec);
    }
}

void PaintArea::loadFromFile()
{
    // source: http://doc.qt.io/qt-5/qtwidgets-tutorials-addressbook-part6-example.html
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load picture"), "",
        tr("PNG (*.png);;JPG (*.jpg *.jpeg);;All Files (*)"));

    if (fileName.isEmpty()){
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("No file selected."));
        return;
    }

    if (pixmap.load(fileName) == false){
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load picture %1.")
                                 .arg(QDir::toNativeSeparators(fileName)));
        return;
    } else {
        delete(image);
        image = new QPixmap(pixmap);
        this->resize(image->size());

        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Picture successfully load."));
    }

    this->update();
}

void PaintArea::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save picture"), "",
        tr("PNG (*.png);;JPG (*.jpg *.jpeg);;All Files (*)"));

    if (fileName.isEmpty()){
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("No filename selected."));
        return;
    }

    if (image->save(fileName) == false){
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot save picture %1:.")
                                 .arg(QDir::toNativeSeparators(fileName)));
        return;
    } else {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Picture successfully save."));
    }
}



void PaintArea::paintObject(
        PaintType type, int x1, int y1, int x2, int y2, int penWidth) {
    QPainter paint;
    //paint.setRenderHint(QPainter::Antialiasing);
    paintActivate = false;
    paint.begin(image);

    static int localePenWidth;
    localePenWidth = actualPenWidth;
    if(penWidth > -1)
        localePenWidth = penWidth;

    static QColor localPenColor;
    localPenColor = actualPenColor;
    if(type == PaintType::rubber)
        localPenColor = Qt::white;

    paint.setPen(QPen(localPenColor, localePenWidth, actualPenStyle, Qt::RoundCap, Qt::RoundJoin));
    paint.setBrush(localPenColor);

    // drawCircle
    static int x_y = 0;
    static int xDelta = 0;
    static int yDelta = 0;
    static int xSign = 1;
    static int ySign = 1;

    switch (type) {
        case PaintType::line:
            paint.drawLine(x1,y1,x2,y2);
            qDebug() << "drawLine";
            break;

        case PaintType::circle:
            xDelta = x2-x1;
            yDelta = y2-y1;
            x_y = qMin(qAbs(xDelta), qAbs(yDelta));

            xSign = (xDelta < 0) ? -1 : 1;
            ySign = (yDelta < 0) ? -1 : 1;

            paint.drawEllipse(x1, y1, x_y*xSign, x_y*ySign);
            qDebug() << "drawCircle";
            break;

        case PaintType::rect:
            paint.drawRect(x1,y1,x2-x1,y2-y1);
            qDebug() << "drawRect";
            break;

        case PaintType::ellipse:
            paint.drawEllipse(x1,y1,x2-x1,y2-y1);
            qDebug() << "drawEllipse";
            break;

        case PaintType::curve:
            paint.drawPolyline(drawPoints); // TODO
            qDebug() << "drawPolygon";
            break;

        case PaintType::pen:
            paint.drawPolyline(drawPoints);
            qDebug() << "drawPen";
            break;

        case PaintType::brush:
            paint.drawPolyline(drawPoints); //TODO
            qDebug() << "drawBrush";
            break;

        case PaintType::rubber:
            paint.drawPoint(x2,y2);
            qDebug() << "drawRubber";
            break;

        default:
            break;
    }

    qDebug() << static_cast<int>(actualPaintType);

    qDebug() << "x: " << x1 << " -> " << x2 << " (" << x2-x1 << ")  "
             << "y: " << y1 << " -> " << y2 << " (" << y2-y1 << ")\n";
    paint.end();
    paintActivate = true;
    this->update();
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    imageBeforeMouseMoveEvent = image->copy();
    x = event->x();
    y = event->y();

    QPoint point(x, y);
    if(actualPaintType == PaintType::curve){
        drawPoints.clear();
        drawPoints.append(point);

        curvePoints.clear();
        curvePoints.append(point);
    }

    this->update();
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(actualPaintType == PaintType::rubber) {
        delete image;
        image = new QPixmap(imageBeforeMouseMoveEvent);
    }
    paintObject(actualPaintType, x, y, event->x(), event->y());
    this->update();
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point(event->x(), event->y());

    if(actualPaintType == PaintType::curve){
        drawPoints.append(point);
        curvePoints.append(point);
    }

    if(actualPaintType != PaintType::pen &&
       actualPaintType != PaintType::brush)
    {
        delete image;
        image = new QPixmap(imageBeforeMouseMoveEvent);
    }

    paintObject(actualPaintType, x, y, event->x(), event->y());

    if(actualPaintType == PaintType::rubber) {
        imageBeforeMouseMoveEvent = image->copy();
        paintObject(PaintType::circle,
                    event->x()-actualPenWidth/2,
                    event->y()-actualPenWidth/2,
                    event->x()+actualPenWidth/2,
                    event->y()+actualPenWidth/2, 1);
    }


    this->update();
}


