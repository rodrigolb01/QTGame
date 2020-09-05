#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
/*entity with purpose of collide with other entities
 * If it collids with a player, it reduces it's health and destoy the bullet.
 * If it collides with enemy, it destroys the enemy and the bullet.
 * If it collides with another bullet, both are destoyed.
*/

class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent=0, int angle=1);
    QPixmap bulletpic;
    bool friendlyFire = false; /* if a bullet is allowed to destroy a sender of its own kind, disabled for enemies
                                 *(just a temporary solution for enemies destroying themselves)
                                 */

public slots:
    void move();
private:
    int angle;
};

#endif // BULLET_H
