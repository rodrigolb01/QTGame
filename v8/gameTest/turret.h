#ifndef TURRET_H
#define TURRET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPointF>


class Turret: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Turret(QGraphicsItem *parent=0);
    double distanceTo(QGraphicsItem *item);
    bool hasTarget;
    bool hasEnemies;
    QGraphicsPolygonItem *attack_area;

public slots:
    void attackTarget();
    void acquireTarget();

private:
    QPointF attack_dest;
    QPixmap turretpic;

};

#endif // TURRET_H
