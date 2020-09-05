#include "MyRect.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <bullet.h>
#include "enemy.h"


MyRect::MyRect(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    bullet_sound = new QMediaPlayer();
    bullet_sound->setMedia((QUrl("qrc:/sounds/sounds/shoot2.wav")));
    setPixmap(QPixmap(":/images/img/wr.png"));
}

void MyRect::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Left)
    {
        if(this->pos().x()>=0 )
        {
            setPos(x()-10,y());
        }

    }
    else if(event->key() == Qt::Key_Right)
    {
        if(this->pos().x() <= scene()->height() + this->pixmap().height())
        {
           setPos(x()+10,y());
        }

    }
    else if(event->key() == Qt::Key_Up)
    {
        if(this->pos().y() >= 0)
        {
            setPos(x(),y()-10);
        }

    }
    else if(event->key() == Qt::Key_Down)
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

void MyRect::spawn()
//create an enemy
{
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);

}
