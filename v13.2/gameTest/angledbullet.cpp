#include "angledbullet.h"
#include <QTimer>
#include <qmath.h>
#include "turret.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"

extern Game* game;

angledBullet::angledBullet(QGraphicsItem *parent, int bulletShooter): QGraphicsItem(parent)
{
    this->bulletShooter = bulletShooter;
    bulletPic = new QPixmap(":/images/img/beam.png");
    moveTimer = new QTimer(this);
    animationTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &angledBullet::move);
    connect(animationTimer, &QTimer::timeout, this, &angledBullet::nextFrame);
    moveTimer->start(50);
    animationTimer->start(50);

    currentFrame=70;
    currentRow=0;
    animationEnd=140;

    hide();//hide until it leaves contact with turret spawnpoint and reaches the end of the turret barrel
}

void angledBullet::nextFrame()
{
    currentFrame +=70;
    if(currentFrame >= animationEnd)
    {
        currentFrame=70;
        animationStarted=false;
        if(animationEnd==700)
        {
            game->scene->removeItem(this);
            return;
        }
    }
    this->update(-35,-35,70,70);
}

void angledBullet::move()
{
    int STEP_SIZE =30;
    double theta = rotation();//degrees

    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));
    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    // this block of code make the bullet looks like is coming from the barrel of the gun, not the center of the turret
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(size_t i=0, n=colliding_items.size(); i<n; i++)
    {
        if(typeid (*(colliding_items[i])) == typeid(Turret))
        {
            hide();
        }
        if(colliding_items.size()>=2)
        {
            show();
        }

        if(typeid (*(colliding_items[i])) == typeid (Player) && bulletShooter == 2)// enemy fire
        {
            game->player1->info->health->decrease();
            game->scene->removeItem(this);
            delete this;
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

        if(typeid (*(colliding_items[i])) == typeid (Bullet)) //&& bullet shooted by the opposite
        {
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }

    }

    if(animationStarted==false)
    {
        setPos(x() +dx, y() +dy);
    }

   if(!game->mothership1->t->attack_area->contains(this->pos()))//delete the bullet if it is in max range
   {
       delete this;
       return;
   }
}

void angledBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-35,-35, *bulletPic, currentFrame, currentRow, 70,70);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF angledBullet::boundingRect() const
{
    return QRectF(-40,-30,80,60);
}
