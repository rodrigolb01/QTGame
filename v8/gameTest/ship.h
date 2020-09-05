#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include "turret.h"

class Ship : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Ship(QObject *parent = nullptr);
    double distanceTo(QGraphicsItem *item);
    Turret *t;

private:
    QGraphicsPolygonItem *boundingPolygon;
    QPixmap *shipPic;
    bool hasTarget;
    bool hasEnemies;
};

#endif // SHIP_H
