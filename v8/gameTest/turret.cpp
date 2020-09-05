#include "turret.h"
#include "QTimer"
#include <QGraphicsItem>
#include "angledbullet.h"
#include "game.h"
#include "enemy.h"

extern Game * game;


Turret::Turret(QGraphicsItem *parent) :QGraphicsPixmapItem(parent)
{
    turretpic = QPixmap(":/images/img/turret1.png");
    setPixmap(turretpic);

     this->setTransformOriginPoint(pos().x()+10,pos().y()+25);

     //create an octagon in a 11x11 space as the turret range of view
     QVector<QPointF> points;
     points <<QPointF(1.5,1.5) <<QPointF(5.5,0) <<QPointF(9.5,1.5) <<QPointF(11,5.5) <<QPointF(9.5,9.5) <<QPointF(5.5,11) <<QPointF(1.5,9.5) <<QPointF(0,5.5);
     int SCALE_FACTOR = 65;

     for(size_t i=0, n=points.size(); i<n; i++)
     {
         points[i] *= SCALE_FACTOR;
     }

     attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);
     //align polygon center with sprite center

     QPointF polygonCenter(5.5,5.5);
     polygonCenter *= SCALE_FACTOR;
     polygonCenter = mapToScene(polygonCenter);
     QPointF turretCenter(x()+10,y()+17);
     QLineF ln(polygonCenter, turretCenter);
     attack_area->setPos(x()+ln.dx(),y()+ln.dy());

     QTimer *timer = new QTimer();
     connect(timer, SIGNAL(timeout()),this,SLOT(acquireTarget()));
     timer->start(1000);
 }

 double Turret::distanceTo(QGraphicsItem *item)
 {
     QLineF ln(pos(),item->pos());
     return ln.length();
 }

 void Turret::attackTarget()
 {
      angledBullet *p = new angledBullet();

     QLineF ln(QPointF(x()-40,y()),attack_dest);
     int angle = -1 *ln.angle(); //rotate anti-clockwise
     p->setPos(x()-40,y());

     p->setRotation(angle);//rotate bullet
     this->setRotation(angle-270);//rotate turret
     game->scene->addItem(p);
     qDebug() << "items at scene: " << game->scene->items().size();
 }

 void Turret::acquireTarget()
 {
     QList<QGraphicsItem*> colliding_items = attack_area->collidingItems();//make a list of all colliding items and verify if there is enemies.
     for(size_t i=0, n=colliding_items.size(); i<n; i++)
     {
         if(typeid (*colliding_items[i]) ==typeid (Enemy))
         {
             hasEnemies=true;//check if there is an enemy in range
             break;
         }
         hasEnemies=false;
         this->setRotation(0);
     }
     if(hasEnemies)//if there is, get witch objects from the list are enemies ad find the closest one.
     {
         double closestDistance = 400;
         QPointF closestPoint = QPointF(0,0);
         for(size_t j=0, m=colliding_items.size(); j<m; j++)
         {
             Enemy *enemy = dynamic_cast<Enemy*>(colliding_items[j]);
             if(enemy)
             {
                 double thisDistance = distanceTo(enemy);
                 if(thisDistance < closestDistance)
                 {
                     closestDistance = thisDistance;//set target to closest enemy
                     closestPoint = colliding_items[j]->pos();
                     hasTarget=true;
                 }
             }
         }
         attack_dest = closestPoint;
         attackTarget();//fire!
     }
     else
     {
         hasTarget=false;
         return;
      }
 }
