#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "enemy.h"
#include <QList>
#include "game.h"

extern Game * game;// there is a external global object called game

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/img/beam.png"));
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
            game->score->increase();
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
    if(this->pos().y()== 0 - this->pixmap().height())
    {
        delete this;
    }

}
