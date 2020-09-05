#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>

Enemy::Enemy() : QObject(), QGraphicsRectItem()
{
    //set random position
    int random_number = rand()% 700;
    setPos(random_number,0);

    //draw rectangle
    setRect(0,0,100,100);
    //connect
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(move()));


    timer->start(50);




}

void Enemy::move()
{
    setPos(x(),y()+5);
    if(this->pos().y() + rect().height() < 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
