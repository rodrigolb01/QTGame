#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QGraphicsRectItem>
#include <QObject>

class EnemyBullet: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    EnemyBullet();
public slots:
    void move();
};

#endif // ENEMYBULLET_H
