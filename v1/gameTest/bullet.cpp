#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "enemy.h"
#include <QList>

Bullet::Bullet()
{
    //draw rectangle
    setRect(0,0,10,50);
    //connect
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(move()));

    timer->start(50);
}

void Bullet::move()
// if bullet collides with enemy, destroy both
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid (*(colliding_items[i])) == typeid (Enemy))
        {
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            // delete them both
            delete colliding_items[i];
            delete this;
            return;
        }
    }
    // move bullet up
    setPos(x(),y()-10);
    if(this->pos().y()== 0 - this->rect().height())
    {
        delete this;
    }
}
