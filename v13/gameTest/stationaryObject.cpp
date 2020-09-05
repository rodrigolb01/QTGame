#include "stationaryObject.h"
#include <QPainter>
#include <QTimer>
#include "game.h"



StationaryObject::StationaryObject(QObject *parent)
{
    spriteImage = new QPixmap(":/images/img/debris1.png");
}

void StationaryObject::move(int direction)
{
    if(direction == 70)
       this->setPos(x(),y()-20);
    if(direction == 140)
        this->setPos(x()+20,y());
    if(direction == 210)
       this-> setPos(x(),y()+20);
    if(direction == 0)
        this->setPos(x()-20,y());
}

QRectF StationaryObject::boundingRect() const
{
    return QRectF(-35,-25,70,50);
}

void StationaryObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-35,-25, *spriteImage, 0, 0, 70,50);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
