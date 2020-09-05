#include <stdlib.h>
#include "enemy.h"
#include "player.h"
#include <QBitmap>
#include "bullet.h"
#include "game.h"
#include "stdlib.h"


extern Game *game;

using namespace std;

Enemy::Enemy(QObject *parent):
    QObject(parent), QGraphicsItem()
{
    spriteImage = new QPixmap(":/images/img/hizack spritesheet.png");

    int random_number = rand()% 1200;
    setPos(random_number,0);

    currentFrame=0;
    currentSequence=210;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::nextFrame);
    timer->start(100);

    timer2 = new QTimer();
    connect(timer2, &QTimer::timeout, this, &Enemy::move);

    timer2->start(10);

    timer3 = new QTimer();
    connect(timer3, &QTimer::timeout, this, &Enemy::enemiesInrange);
    timer3->start(1000);
}

void Enemy::move()
{
    //stop this enemy if the player is in it's range and attack player
    //start chasing until is out of range

    int xorigin = this->pos().x()-20;
    int yorigin = this->pos().y()+50;

    if(game->player1->pos().x() <= xorigin + 200 && game->player1->pos().x() >= xorigin - 200)//if player is in it;s horizontal rangez
    {
        if(game->player1->pos().y() <= yorigin + 400 && game->player1->pos().y() >= yorigin)// turn forward
        {
            currentSequence = 210;// if is in it's front
            if(game->player1->pos().x() >= xorigin)
            {
                setPos(this->pos().x()+1,this->pos().y());//move right
            }
            if(game->player1->pos().x() <= xorigin)
            {
                setPos(this->pos().x()-1,this->pos().y());//left
            }
        }
        else if(game->player1->pos().y() >= yorigin - 400 && game->player1->pos().y() <= yorigin)//turn back
        {
            currentSequence = 70;
            if(game->player1->pos().x() >= xorigin)
            {
                setPos(this->pos().x()+1,this->pos().y());//move right
            }
            if(game->player1->pos().x() <= xorigin)
            {
                setPos(this->pos().x()-1,this->pos().y());//left
            }

        }

    }
    else if(game->player1->pos().x() > xorigin + 200 && game->player1->pos().x() <= xorigin + 400)
    {
        currentSequence = 140;
        if(game->player1->pos().y() <= yorigin )
        {
            setPos(this->pos().x(),this->pos().y()-1);
        }
        if(game->player1->pos().y() >= yorigin  )
        {
            setPos(this->pos().x(),this->pos().y()+1);
        }
    }
    else if(game->player1->pos().x() < xorigin - 200 && game->player1->pos().x() >= xorigin - 400)
    {
        currentSequence = 0;
        if(game->player1->pos().y() <= yorigin)
        {
            setPos(this->pos().x(),this->pos().y()-1);
        }
        if(game->player1->pos().y() >= yorigin)
        {
            setPos(this->pos().x(),this->pos().y()+1);
        }
    }

    else //keep going straight
    {
        currentSequence = 210;
        setPos(x(),y()+0.25);
    }
    if(pos().y() + spriteImage->height() < 0 || pos().y() >= 800)
    {
        game->scene->removeItem(this);
        delete this;
        return;
    }
}

void Enemy::shoot()
{
    if(currentSequence == 210)
    {
        Bullet * bullet = new Bullet(0,currentSequence,20,2);
        bullet->setPos(this->pos().x()-20,this->pos().y()+50);
        scene()->addItem(bullet);
    }
    else if(currentSequence == 70)
    {
         Bullet * bullet = new Bullet(0,currentSequence,30,2);
         bullet->setPos(this->pos().x()-20,this->pos().y()-80);
         scene()->addItem(bullet);
    }
    else if(currentSequence == 140)
    {
         Bullet * bullet = new Bullet(0,currentSequence,30,2);
         bullet->setPos(this->pos().x()+20 ,this->pos().y()-50 );
         scene()->addItem(bullet);
    }
    else if(currentSequence == 0)
    {
        Bullet * bullet = new Bullet(0,currentSequence,30,2);
        bullet->setPos(this->pos().x()-50 ,this->pos().y()-50 );
        scene()->addItem(bullet);
    }
}
void Enemy::slash()
{

}

void Enemy::enemiesInrange()
{
    if(game->player1->pos().x() <= this->pos().x()+180 && game->player1->pos().x() >= this->pos().x()-220)
    {
        shoot();
    }
    if(game->player1->pos().y() == this->pos().y()+50)
    {

        shoot();
    }

}


void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-35,-35, *spriteImage, currentFrame, currentSequence, 70,70);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Enemy::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}

void Enemy::nextFrame()
{
    currentFrame += 70;
    if (currentFrame >= 210)
        currentFrame = 0;
    this->update(-35,-35,70,70);
}
