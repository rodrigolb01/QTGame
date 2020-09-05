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
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::nextFrame);
    timer->start(100);

    timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, this, &Enemy::move);

    timer2->start(2);

    timer3 = new QTimer(this);
    connect(timer3, &QTimer::timeout, this, &Enemy::shoot);
    timer3->start(1000);
}

void Enemy::move()
{

        currentSequence = 210;
        setPos(x(),y()+0.25);

    if(pos().y() + spriteImage->height() < 0 || pos().y() >= 800)
    {
        game->scene->removeItem(this);
        delete this;
        return;
    }

    if(pos().x() >= 600 || pos().x() == 0)
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


void Enemy::enemiesInrange()//fires player if him is at range
{
    qInfo() << "Items in scene: " << scene()->items().size();

    if(game->player1->pos().y() <= this->pos().y()+300 )
    {
        if(game->player1->pos().x() <= this->pos().x()+100 && game->player1->pos().x()>= this->pos().x()-100)
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
