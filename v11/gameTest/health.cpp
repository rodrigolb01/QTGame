#include "health.h"
#include <QFont>
#include "game.h"

extern Game* game;

Health::Health(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    // initialize health to 10
    health = 10;

    // draw the text
    setPlainText(QString("Health: ") + QString::number(health));
    setFont(QFont("times",10));
    setDefaultTextColor(Qt::red);
    setPos(1080,150);
}

void Health::decrease()
{
   if(health>0)
   {
       health--;
       setPlainText(QString("Health: ") + QString::number(health));
   }
}

void Health::increase()
{
    if(health<100)
    {
        health++;
        setPlainText(QString("Health: ") + QString::number(health));
    }
}

int Health::getHealth()
{
    return health;
}
