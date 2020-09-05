#ifndef ANGLEDBULLET_H
#define ANGLEDBULLET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class angledBullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit angledBullet(QGraphicsItem *parent=0);

public slots:
    void move();
};

#endif // ANGLEDBULLET_H
