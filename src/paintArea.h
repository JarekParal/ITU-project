#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QPainter>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    QPainter *painter;

    explicit PaintArea(QWidget *parent = 0);


    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QPixmap pixmap;
};

#endif // PAINTAREA_H
