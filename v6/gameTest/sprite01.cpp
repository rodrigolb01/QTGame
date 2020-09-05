#include "sprite01.h"

Sprite01::Sprite01(QObject *parent) : QObject(parent)
{
    currentFrame_spr01 = 0;
    spriteImage01 = new QPixmap(":/images/img/spritewr");

    sprite_timer01 = new QTimer();
    connect(sprite_timer01, SIGNAL(timeout()),this, SLOT(nextFrame()));
    sprite_timer01->start(100);
}

void Sprite01::nextFrame()
{
    currentFrame_spr01 += 300;
    if(currentFrame_spr01 >= 1200)
    {
        this->update(-150,-150,300,300);
    }
}

void Sprite01::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-150,-150, *spriteImage01, currentFrame_spr01,0,300,300);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Sprite01::boundingRect() const
{
    return QRectF(-150,-150,300,300);
}
