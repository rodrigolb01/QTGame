#include "sprite01.h"

Sprite01::Sprite01(QObject *parent):
    QObject(parent), QGraphicsItem()
{
    sprite01_currentFrame = 0;
    sprite01_image = new QPixmap();

    sprite01_timer = new QTimer();
    connect(sprite01_timer, SIGNAL(timeout()),this, SLOT(nextFrame()));
    sprite01_timer->start(100);
}

void Sprite01::nextFrame()
{
   sprite01_currentFrame += 300;
   if(sprite01_currentFrame >= 1200)
   {
       this->update(-150,-150,300,300);
   }
}

void Sprite01::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-150,-150, *sprite01_image, sprite01_currentFrame, 0, 300, 300);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Sprite01::boundingRect() const
{
    return QRectF(-150, -150, 300, 300);
}
