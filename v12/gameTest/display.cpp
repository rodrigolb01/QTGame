#include "display.h"
#include <QPainter>
#include <QRectF>


Display::Display(QObject *parent) : QObject(parent)
{
    pic = new QPixmap(":/images/img/screen.png");
}

void Display::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-109,-111,*pic,0,0,218,222);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF Display::boundingRect() const
{
    return QRectF(-109,-111,218,222);
}
