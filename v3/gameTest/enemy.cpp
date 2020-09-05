#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <enemybullet.h>

Enemy::Enemy() : QObject(), QGraphicsRectItem()
{
    //set random position
    int random_number = rand()% 700;
    setPos(random_number,0);

    //draw rectangle
    setRect(0,0,100,100);
    //connect
    QTimer * timer = new QTimer();
    QTimer * timer2 = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(move()));
    connect(timer2, SIGNAL(timeout()),this, SLOT(shoot()));


    timer->start(50);
    timer2->start(2000);

}

void Enemy::move()
{
    setPos(x(),y()+2);
    if(this->pos().y() + rect().height() < 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}

void Enemy::shoot()
{
    EnemyBullet * bullet = new EnemyBullet();
    bullet->setPos(x(),y());
    scene()->addItem(bullet);
}
