#include "spritesegment.h"

SpriteSegment::SpriteSegment(QPixmap* picture, QObject *parent) : QObject(parent)
{
    this->picture = picture;
}

void SpriteSegment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(-35,-35,*picture,x,y,70,70);
}

QRectF SpriteSegment::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}
