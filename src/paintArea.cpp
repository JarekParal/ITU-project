#include "paintArea.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    //To allow paint events outside of paintEvent
    //setAttribute(Qt::WA_StaticContents);

    actualPaintType = PaintType::line;

    image = new QPixmap(800, 800);
    image->fill(Qt::white);

    QPainter paint;
    paint.begin(image);
    paint.setPen(QColor(Qt::blue));
    paint.drawLine(0,0,100,100);
    paint.end();

    paintActivate = true;
}

QSize PaintArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize PaintArea::sizeHint() const
{
    return QSize(800, 800);
}

void PaintArea::paintEvent(QPaintEvent * event)
{
    if(paintActivate == true) {
        QPainter painter(this);
        QRect rec = event->rect();
        painter.drawPixmap(rec, *image, rec);
    }

//    paint.drawPixmap(0,0,pixmap);

//    paint.setPen(QColor(Qt::blue));
//    paint.drawLine(0,0,100,100);

//    QBrush fillBrush;
//    fillBrush.setColor(Qt::red);
//    fillBrush.setStyle(Qt::SolidPattern);

//    //paint.fillPath(painterPath, fillBrush);
//    paint.drawPath(painterPath);
}

void PaintArea::loadFromFile()
{
    // source: http://doc.qt.io/qt-5/qtwidgets-tutorials-addressbook-part6-example.html
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load pictures"), "",
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

        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Picture successfully load."));

    }

    this->update();
}

void PaintArea::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Load pictures"), "",
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

void PaintArea::paintObject(PaintType type, int x1, int y1, int x2, int y2) {
    QPainter paint;
    paintActivate = false;
    paint.begin(image);
    paint.setPen(QColor(Qt::blue));

    switch (type) {
        case PaintType::line:
            paint.drawLine(x1,y1,x2,y2);
            qDebug() << "drawLine";
            break;

        case PaintType::circle:
            paint.drawEllipse(x1,y1,x2-x1,y2-y1);
            qDebug() << "drawEllipse";
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
            paint.drawLine(x1,y1,x2,y2);
            qDebug() << "drawLine";
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
    x = event->x();
    y = event->y();

    this->update();
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    paintObject(actualPaintType, x, y, event->x(), event->y());

    this->update();
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->update();
}


