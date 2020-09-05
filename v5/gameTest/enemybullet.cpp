#include "enemybullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "enemy.h"
#include <QList>
#include "game.h"

extern Game * game;// there is a extern global object called game

EnemyBullet::EnemyBullet()
{
    setPixmap(QPixmap(":/images/img/beam.png"));
    // connect
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(move()));

    timer->start(50);
}

void EnemyBullet::move()
// if bullet collides with player destoy bullet and reduce player's health
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i < n; ++i)
    {
        if(typeid (*(colliding_items[i])) == typeid (MyRect))
        {
            game->health->decrease();
            scene()->removeItem(this);
            delete this;

            return;
        }
    }

    //move bullet down
    this->setPos(x(), y() + 20);
    if(this->pos().y() >= 400)
    {
        delete this;
    }
}
