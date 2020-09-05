#include "angledbullet.h"
#include <QTimer>
#include <qmath.h>
#include "turret.h"
#include "game.h"

extern Game* game;

angledBullet::angledBullet(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{

    this->setTransformOriginPoint(pos().x()+40,pos().y()+25);


    QTimer * timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &angledBullet::move);
    timer->start(50);

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

    }
    if(colliding_items.size()==3)
    {
        show();
    }
    //
    QPixmap bulletpic = QPixmap(":/images/img/beam1.png");
    setPixmap(bulletpic);

    setPos(x() +dx, y() +dy);

   if(!game->mothership1->t->attack_area->contains(this->pos()))
   {
       delete this;
       return;
   }
}
