#include "paintArea.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
//    painter = new QPainter(this);

//    pixmap.load(":/images/qt-logo.png");
//    painter->drawPixmap(0,0,pixmap);

    painterPath.addRect(10, 10, 120, 120);


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

    QBrush fillBrush;
    fillBrush.setColor(Qt::red);
    fillBrush.setStyle(Qt::SolidPattern);

    //paint.fillPath(painterPath, fillBrush);
    paint.drawPath(painterPath);
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

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly) == false){
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot open file for saving picture."));
        return;
    }

    QImage picture;
    QPainter painter;
    painter.begin(&picture);
    painter.drawPath(painterPath);
    painter.end();

    QImageWriter imagefile; // = QImageWriter();
    imagefile.setFileName(fileName);
    imagefile.setFormat("png");
    imagefile.setQuality(100);

    if (imagefile.write(picture) == false){
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot save picture %1: %2.")
                                 .arg(QDir::toNativeSeparators(fileName), imagefile.errorString()));
        return;
    } else {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Picture successfully save."));

    }
}
