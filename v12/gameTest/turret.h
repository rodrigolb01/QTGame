#ifndef TURRET_H
#define TURRET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include "infoturret.h"
#include "hpbar.h"


class Turret: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Turret(QGraphicsItem *parent=0);
    HPbar* hpBar;
    double distanceTo(QGraphicsItem *item);
    bool hasTarget;                          //initially no target to lock in.
    bool enemiesInRange;                     //if there is any enemies in this turret range, it will lock in.
    QGraphicsPolygonItem *attack_area;       //range of this turret
    InfoTurret *turretInfo;

public slots:
    void attackTarget();
    void acquireTarget();

private:
    QPointF attack_dest;
    QPixmap turretpic;
};

#endif // TURRET_H
