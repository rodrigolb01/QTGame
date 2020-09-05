#include <stdlib.h>
#include "spritee.h"
#include "sprite.h"
#include <QBitmap>
#include "bullet.h"
#include "game.h"

extern Game *game;

spriteE::spriteE(QObject *parent):
    QObject(parent), QGraphicsItem()
{
    spriteImage = new QPixmap(":/images/img/hizack spritesheet.png");

    int random_number = rand()% 1200;
    setPos(random_number,0);

    currentFrame=0;
    currentAngle=210;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &spriteE::nextFrame);
    timer->start(100);

    timer2 = new QTimer();
    connect(timer2, &QTimer::timeout, this, &spriteE::move);

    timer2->start(10);

    timer3 = new QTimer();
    connect(timer3, &QTimer::timeout, this, &spriteE::enemiesInrange);
    timer3->start(1000);
}

void spriteE::move()
{
    //stop this enemy if the player is in it's range and attack player
    //start chasing until is out of range

    int xorigin = this->pos().x()-20;
    int yorigin = this->pos().y()+50;

    if(game->player1->pos().x() <= xorigin + 200 && game->player1->pos().x() >= xorigin - 200)//if player is in it;s horizontal range
    {
        if(game->player1->pos().y() <= yorigin + 400 && game->player1->pos().y() >= yorigin)// turn forward
        {
            currentAngle = 210;// if is in it's front
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
            currentAngle = 70;
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
        currentAngle = 140;
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
        currentAngle = 0;
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
        currentAngle = 210;
        setPos(x(),y()+0.25);
    }
    if(this->pos().y() + spriteImage->height() < 0 || this->pos().y() >= scene()->height())
    {
        game->scene->removeItem(this);
        delete this;
    }
}

void spriteE::shoot()
{
    if(currentAngle == 210)
    {
        Bullet * bullet = new Bullet(0,currentAngle);
        bullet->setPos(this->pos().x()-20,this->pos().y()+50);
        scene()->addItem(bullet);
    }
    else if(currentAngle == 70)
    {
         Bullet * bullet = new Bullet(0,currentAngle);
         bullet->setPos(this->pos().x()-20,this->pos().y()-80);
         scene()->addItem(bullet);
    }
    else if(currentAngle == 140)
    {
         Bullet * bullet = new Bullet(0,currentAngle);
         bullet->setPos(this->pos().x()+20 ,this->pos().y()-50 );
         scene()->addItem(bullet);
    }
    else if(currentAngle == 0)
    {
        Bullet * bullet = new Bullet(0,currentAngle);
        bullet->setPos(this->pos().x()-50 ,this->pos().y()-50 );
        scene()->addItem(bullet);
    }
}
void spriteE::slash()
{

}

void spriteE::enemiesInrange()
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

void spriteE::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-35,-35, *spriteImage, currentFrame, currentAngle, 70,70);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF spriteE::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}

void spriteE::nextFrame()
{
    currentFrame += 70;
    if (currentFrame >= 210)
        currentFrame = 0;
    this->update(-35,-35,70,70);
}
