#include "sprite03.h"

Sprite03::Sprite03(QObject *parent) : QObject(parent)
{
    currentFrame_spr03 = 0;
    spriteImage03 = new QPixmap(":/images/img/spritewr3.png");

    sprite_timer03 = new QTimer();
    connect(sprite_timer03, SIGNAL(timeout()),this, SLOT(nextFrame()));
    sprite_timer03->start(100);
}

void Sprite03::nextFrame()
{
    currentFrame_spr03 += 300;
    if(currentFrame_spr03 >= 1200)
    {
        this->update(-150,-150,300,300);
    }
}

void Sprite03::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-150,-150, *spriteImage03, currentFrame_spr03,0,300,300);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Sprite03::boundingRect() const
{
    return QRectF(-150,-150,300,300);
}
