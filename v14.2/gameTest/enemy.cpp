#include <stdlib.h>
#include "enemy.h"
#include "player.h"
#include <QBitmap>
#include "bullet.h"
#include "angledbullet.h"
#include "game.h"
#include "stdlib.h"
#include "qmath.h"
#include "eff_explosion.h"


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
    //connect(timer2, &QTimer::timeout, this, &Enemy::move);

    timer2->start(2);

    timer3 = new QTimer(this);
    connect(timer3, &QTimer::timeout, this, &Enemy::shoot);
    timer3->start(1000);

    //set points
    points << QPointF(200,200) << QPointF(200,400);
    points_index = 0;
    dest = game->player1->pos();

    rotateToPoint(game->player1->pos());

    QTimer* mvtimer = new QTimer(this);
    connect(mvtimer, &QTimer::timeout, this, &Enemy::move_forward);
    mvtimer->start(150);

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
    qInfo() << "angle: " << rotation();
    angledBullet * bullet = new angledBullet(0,2);
    if(currentSequence == 210)
    {
        bullet->setPos(this->pos().x()-20,this->pos().y()+50);
    }
    else if(currentSequence == 70)
    {
         bullet->setPos(this->pos().x()-20,this->pos().y()-80);
    }
    else if(currentSequence == 140)
    {
         bullet->setPos(this->pos().x()+20 ,this->pos().y()-50 );
    }
    else if(currentSequence == 0)
    {
        bullet->setPos(this->pos().x()-50 ,this->pos().y()-50 );
    }

    QLineF ln(pos(),game->player1->pos());
    int angle = -1 *ln.angle(); //rotate anti-clockwise
    bullet->setPos(x()+10,y()+17);

    bullet->setRotation(angle);//rotate bullet
    scene()->addItem(bullet);
}

double Enemy::rotateToPoint(QPointF p)
{
    QLineF ln(pos(),p);
    //setRotation(-1 * ln.angle());
    int angl =(-1 * ln.angle());

    return angl;
}

void Enemy::move_forward()
{
    //rotateToPoint(game->player1->pos());

    int STEP_SIZE = 5;
    double theta = rotateToPoint(game->player1->pos());;
    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    if(theta <= -225 && theta >= -315)
    {
        currentSequence = 210;
    }
    else if(theta <= -135 && theta >= -225)
    {
        currentSequence = 0;
    }
    else if(theta <= -45 && theta >= -135)
    {
        currentSequence = 70;
    }
    else if(theta <= 0 && theta >= -45)
    {
        currentSequence = 140;
    }

    setPos(x()+dx,y()+dy);
}

void Enemy::enemiesInrange()//fires player if him is at range
{

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
