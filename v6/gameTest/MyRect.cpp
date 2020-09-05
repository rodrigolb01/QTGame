#include "MyRect.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <bullet.h>
#include "enemy.h"
#include <QGridLayout>
#include <QPainter>
#include <QTimer>
#include "game.h"
#include "sprite01.h"
#include "sprite02.h"
#include "sprite03.h"

Sprite01 *eff01;
Sprite02 *eff02;
Sprite03 *eff03;

extern Game *game;

MyRect::MyRect(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    bullet_sound = new QMediaPlayer();
    bullet_sound->setMedia((QUrl("qrc:/sounds/sounds/shoot2.wav")));

    setPixmap(QPixmap(":/images/img/wr.png"));
}

void MyRect::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_A)
    {
        if(this->pos().x()>=0 )
        {
            eff03 = new Sprite03;
            eff03->setPos(this->pos().x()+120, this->pos().y()+150);
            game->scene->addItem(eff03);
            setPixmap(QPixmap(""));
            setPos(x()-10,y());
        }

    }
    else if(event->key() == Qt::Key_D)
    {
        if(this->pos().x() <= scene()->height() + this->pixmap().height())
        {
           eff02 = new Sprite02;
           eff02->setPos(this->pos().x()+160, this->pos().y()+150);
           game->scene->addItem(eff02);
           setPixmap(QPixmap(""));
           setPos(x()+10,y());
        }

    }
    else if(event->key() == Qt::Key_W)
    {
        if(this->pos().y() >= 100)
        {
            eff01 = new Sprite01;
            eff01->setPos(this->pos().x()+150, this->pos().y()+140);
            game->scene->addItem(eff01);
            setPixmap(QPixmap(""));
            setPos(x(),y()-10);
        }

    }
    else if(event->key() == Qt::Key_S)
    {
        if(this->pos().y() + this->pixmap().height() < scene()->height())
        {
            setPos(x(), y()+10);
        }

    }

    else if (event->key() == Qt::Key_Space)
    {
        // create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(x(),y());
        scene()->addItem(bullet);
        // play bullet_sound
        if(bullet_sound->state() == QMediaPlayer::PlayingState)
        {
            bullet_sound->setPosition(0);
        }
        else if(bullet_sound->state() == QMediaPlayer::StoppedState)
        {
            bullet_sound->play();
        }
    }
}

void MyRect::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        game->scene->removeItem(eff01);
        setPixmap(QPixmap(":/images/img/wr.png"));

    }
    else if(event->key() == Qt::Key_D)
    {
        game->scene->removeItem(eff02);
        setPixmap(QPixmap(":/images/img/wr.png"));

    }
    else if(event->key() == Qt::Key_A)
    {
        game->scene->removeItem(eff03);
        setPixmap(QPixmap(":/images/img/wr.png"));

    }
}

void MyRect::spawn()
//create an enemy
{
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);

}


