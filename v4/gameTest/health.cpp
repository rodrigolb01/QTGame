#include "health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent):QGraphicsTextItem(parent)
{   
    // initialize health to 10
    health = 10;

    // draw the text
    setPlainText(QString("Health: ") + QString::number(health));
    setFont(QFont("times",16));
    setDefaultTextColor(Qt::red);
    setPos(this->pos().x(),this->pos().y() + 25);
}

void Health::decrease()
{
    health--;
    setPlainText(QString("Health: ") + QString::number(health));
}

void Health::increase()
{
    health++;
}

int Health::getHealth()
{
    return health;
}
