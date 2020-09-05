#include "background.h"

Background::Background(QObject *parent) : QObject(parent)
{
    currentframe=1200;
    pic = new QPixmap(":/images/img/background4.png");
    animtimer = new QTimer;
    connect(animtimer,&QTimer::timeout,this,&Background::nextFrame);
    animtimer->start(10);
}

void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-600,-400, *pic, 0, currentframe, 1200, 800);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Background::boundingRect() const
{
    return QRectF(-600,-400,1200,800);
}

void Background::nextFrame()
{
    currentframe -= 1;
    if (currentframe <= 0)
        currentframe = 1200;
    this->update(-600,-400,1200,800);
}
