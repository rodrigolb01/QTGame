#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "enemy.h"
#include <QList>
#include "game.h"

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent, int angle, int bulletStep, int bulletShooter): QObject(), QGraphicsPixmapItem(parent)
{
    bulletpic = QPixmap(":/images/img/beam.png");
    this->angle = angle;
    this->bulletStep = bulletStep;
    this->bulletShooter = bulletShooter;

    if(angle == 0 || angle == 140)//if the direction the bullet is being shooted is horizontal, rotate the img
    {
            setPixmap(bulletpic);
            setTransformOriginPoint(30,40);
            setRotation(90);
    }
    else
            setPixmap(bulletpic);
    //connect
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(move()));

    timer->start(50);
}


void Bullet::move()
// if bullet collides with player destoy bullet and reduce player's health
// if bullet collides with enemy, destroy both
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if(typeid (*(colliding_items[i])) == typeid (Player) && bulletShooter == 2)// && shooter is an enemy
        {
            game->health->decrease();
            game->scene->removeItem(this);
            delete this;
            return;
        }

        if (typeid (*(colliding_items[i])) == typeid (Enemy) && bulletShooter == 1)// && shooter is the player
        {
            game->score->increase();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            // delete them both
            delete colliding_items[i];
            delete this;
            return;
        }

        if(typeid (*(colliding_items[i])) == typeid (Bullet)) //&& bullet shooted by the opposite
        {
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    if(angle == 70) //FORWARD
    {
        // move bullet up
        setPos(x(),y()-bulletStep);
        if(this->pos().y() <= 0 - this->pixmap().height())
        {
            game->scene->removeItem(this);
            delete this;
        }
    }
    if(angle == 210)//BACK
    {
        //move bullet down
        setPos(x(),y()+bulletStep);
        if(this->pos().y() >= game->scene->height())
        {
            game->scene->removeItem(this);
            delete this;
        }
    }
    if(angle == 0) //LEFT
    {
        setPos(x()-bulletStep,y());
        if(this->pos().x() == 0 - this->pixmap().width())
        {
            game->scene->removeItem(this);
            delete this;
        }
    }

    if(angle == 140) // RIGHT
    {
        setPos(x()+bulletStep,y());
        if(this->pos().x() == game->scene->width())
        {
            game->scene->removeItem(this);
            delete this;
        }
    }

}
