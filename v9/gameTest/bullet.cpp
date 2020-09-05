#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "enemy.h"
#include "ship.h"
#include <QList>
#include "game.h"
#include "stationaryObject.h"

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent, int angle, int bulletStep, int bulletShooter): QObject(), QGraphicsItem(parent)
{
    this->angle = angle;
    this->bulletStep = bulletStep;
    this->bulletShooter = bulletShooter;
    currentFrame=0;
    currentRow=0;
    animationEnd = 70;
    bulletPic = new QPixmap(":/images/img/beam.png");

    if(angle == 0 || angle == 140)//if the direction the bullet is being shooted is horizontal, rotate the img
    {
            setTransformOriginPoint(30,40);
            setRotation(90);
    }
    //connect
    moveTimer = new QTimer();
    animationTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()),this, SLOT(move()));
    connect(animationTimer, &QTimer::timeout, this, &Bullet::nextFrame);
    moveTimer->start(50);
    animationTimer->start(50);
}

void Bullet::nextFrame()
{
    currentFrame += 70;
    if (currentFrame >= animationEnd)
    {
        currentFrame=0;
        animationStarted=false;
        if(animationEnd==700)
        {
            game->scene->removeItem(this);
            return;
        }
    }
    this->update(-35,-35,70,70);
}


void Bullet::move()
// if bullet collides with player destoy bullet and reduce player's health
// if bullet collides with enemy, destroy both
// if it collides with another bullet, destroy both
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (size_t i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if(typeid (*(colliding_items[i])) == typeid (Player) && bulletShooter == 2)// enemy fire
        {
            animationStarted=true;
            currentRow=70;//change from beam to explosion
            animationEnd=700;
            nextFrame();
            game->player1->info->health->decrease();
            game->player1->info->hpBar->decrease();
            return;
        }

        if (typeid (*(colliding_items[i])) == typeid (Enemy) && bulletShooter == 1)// player fire
        {
            game->player1->info->score->increase();
            animationStarted=true;
            currentRow=70;//change from beam to explosion
            animationEnd=700;
            nextFrame();

            game->scene->removeItem(colliding_items[i]);
            delete colliding_items[i];
            return;

        }

        if(typeid (*(colliding_items[i])) == typeid (Bullet) && bulletShooter==1) //&& bullet shooted by the opposite
        {
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];

            animationStarted=true;
            currentRow=70;//change from beam to explosion
            animationEnd=700;
            nextFrame();
            return;
        }
        if(typeid (*(colliding_items[i])) == typeid (StationaryObject))
        {
            animationStarted=true;
            currentRow=70;//change from beam to explosion
            animationEnd=700;
            nextFrame();
            return;
        }

        if(typeid (*colliding_items[i]) == typeid(Ship))
        {
            animationStarted=true;
            currentRow=70;//change from beam to explosion
            animationEnd=700;
            nextFrame();
            return;
        }
    }
    if(animationStarted == false)
    {
        if(angle == 70) //FORWARD
        {
            // move bullet up
            setPos(x(),y()-bulletStep);
            if(this->pos().y() <= 0)
            {
                game->scene->removeItem(this);
                delete this;
                return;
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
                return;
            }
        }
        if(angle == 0) //LEFT
        {
            setPos(x()-bulletStep,y());
            if(this->pos().x() <= 0 )
            {
                game->scene->removeItem(this);
                delete this;
                return;
            }
        }

        if(angle == 140) // RIGHT
        {
            setPos(x()+bulletStep,y());
            if(this->pos().x() == game->scene->width())
            {
                game->scene->removeItem(this);
                delete this;
                return;
            }
        }
    }
}

QRectF Bullet::boundingRect() const
{
   return QRectF(-30,-40,60,80  );
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-35,-35, *bulletPic, currentFrame, currentRow, 70,70);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
