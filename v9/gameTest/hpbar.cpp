#include "hpbar.h"
#include "game.h"
#include "player.h"

extern Game* game;

HPbar::HPbar(QObject *parent) : QObject(parent)
{
    bar = new QGraphicsRectItem(QRectF(-lenght/2,4,lenght,8));
    bar->setBrush(Qt::green);
}

void HPbar::increase()
{
    if(lenght<80)
    {
        lenght+=8;
        bar = new QGraphicsRectItem(QRectF(-lenght/2,4,lenght,8));

    }
}

void HPbar::decrease()
{
    if(lenght>0)
    {
        lenght-=8;
        bar->setRect(QRectF(-lenght/2,4,lenght,8));
        if(lenght<60 && lenght >40)
        {
            bar->setBrush(Qt::yellow);
        }
        if(lenght<40)
        {
            bar->setBrush(Qt::red);
        }
        setPos(x()-8,y());
    }
}

QRectF HPbar::boundingRect() const
{
    return QRectF(-50,-4,100,8);
}

void HPbar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
