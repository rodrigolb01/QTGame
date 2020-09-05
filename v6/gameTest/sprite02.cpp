#include "sprite02.h"

Sprite02::Sprite02(QObject *parent) : QObject(parent)
{
    currentFrame_spr02 = 0;
    spriteImage02 = new QPixmap(":/images/img/spritewr2.png");

    sprite_timer02 = new QTimer();
    connect(sprite_timer02, SIGNAL(timeout()),this, SLOT(nextFrame()));
    sprite_timer02->start(100);
}

void Sprite02::nextFrame()
{
    currentFrame_spr02 += 300;
    if(currentFrame_spr02 >= 1200)
    {
        this->update(-150,-150,300,300);
    }
}

void Sprite02::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-150,-150, *spriteImage02, currentFrame_spr02,0,300,300);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Sprite02::boundingRect() const
{
    return QRectF(-150,-150,300,300);
}
