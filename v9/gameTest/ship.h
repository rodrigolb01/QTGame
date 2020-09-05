#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include "turret.h"
#include "infoship.h"

class Ship : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Ship(QObject *parent = nullptr);
    double distanceTo(QGraphicsItem *item);
    Turret *t;
    QGraphicsPolygonItem *boundingPolygon;
    InfoShip *battleshipInfo;

private:
    QPixmap *shipPic;
    bool hasTarget;
    bool hasEnemies;
};

#endif // SHIP_H
