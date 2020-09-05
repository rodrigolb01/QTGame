#include "ship.h"
#include <QPixmap>
#include <QLineF>
#include <QPointF>
#include "bullet.h"
#include "game.h"
#include <QTimer>
#include <angledbullet.h>
#include "enemy.h"


extern Game * game;


Ship::Ship(QObject *parent)
{
    shipPic = new QPixmap(":/images/img/battleship1.png");
    t = new Turret();
    setPixmap(*shipPic);

    QVector<QPointF> points_boundingPolyg;//prepare points for the octagon polygon
    points_boundingPolyg <<QPointF(1.5,0) <<QPointF(2,0) <<QPointF(3,0) <<QPointF(4,0) <<QPointF(4.5,0)
          <<QPointF(4.5,1) <<QPointF(5,1) <<QPointF(5,2) <<QPointF(4.5,2) <<QPointF(4.5,3) <<QPointF(4.5,4)
        <<QPointF(3.5,5.5) <<QPointF(3,5.5) << QPointF(2.5,5.5)<<QPointF(1.5,4) <<QPointF(1.5,3) <<QPointF(1.5,2)
       <<QPointF(1,2) <<QPointF(1,1) <<QPointF(1.5,1) ;
    int SCALE_FACTOR = 65;

    for(size_t i=0, n=points_boundingPolyg.size(); i<n; i++)//scale up the octagon
    {
        points_boundingPolyg[i] *= SCALE_FACTOR;
    }

    boundingPolygon = new QGraphicsPolygonItem(QPolygonF(points_boundingPolyg),this);//set polygons
    QGraphicsItem::prepareGeometryChange();
    boundingPolygon->setTransformOriginPoint(x()+195,y()+181);
    boundingPolygon->setRotation(180);


    QPointF shipArea_polygonCenter(2.5,3);
    shipArea_polygonCenter *= SCALE_FACTOR;
    shipArea_polygonCenter = mapToScene(shipArea_polygonCenter);
    QPointF towerCenter(x()+123,y()+181);
    QLineF ln(shipArea_polygonCenter, towerCenter);
    boundingPolygon->setPos(x()+ln.dx()-32,y()+ln.dy());
    boundingPolygon->hide();
}






