#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
/*object with purpose of collide with other objects
 * If it collids with a player, it reduces it's health and destoy the bullet.
 * If it collides with enemy, it destroys the enemy and the bullet.
 * If it collides with another bullet, both are destoyed.
*/

class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent=0, int angle=1, int bulletSpeed=0, int bulletShooter=0);//angle can't be set 0 as default...
    QPixmap bulletpic;
    int bulletStep; //distance the bullet travels at each timeout
    int bulletShooter; //0 - default, 1 - plater, 2 - enemy

public slots:
    void move();
private:
    int angle;
};

#endif // BULLET_H
