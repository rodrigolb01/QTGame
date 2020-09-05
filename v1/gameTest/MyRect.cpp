#include "MyRect.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <bullet.h>
#include "enemy.h"

#include <QtDebug>
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
        if(this->pos().x() <= scene()->height() + this->rect().height())
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
        if(this->pos().y() + this->rect().height() < scene()->height())
        {
            setPos(x(), y()+10);
        }

    }
    else if (event->key() == Qt::Key_Space)
    {
        Bullet * bullet = new Bullet();
        bullet->setPos(x(),y());
        scene()->addItem(bullet);
    }
}

void MyRect::spawn()
//create an enemy
{
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);

}
