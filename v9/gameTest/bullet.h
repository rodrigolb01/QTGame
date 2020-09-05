#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPainter>

/*object with purpose of collide with other objects
 * If it collids with a player, it reduces it's health and destoy the bullet.
 * If it collides with enemy, it destroys the enemy and the bullet.
 * If it collides with another bullet, both are destoyed.
*/

class Bullet: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet(QGraphicsItem *parent=0, int angle=1, int bulletSpeed=0, int bulletShooter=0);//angle can't be set 0 as default because 0 is a valid angle
    int bulletStep; //distance the bullet travels at each timeout
    int bulletShooter; //0 - default, 1 - plater, 2 - enemy
private slots:
    void nextFrame();
public slots:
    void move();
private:
    int angle;
    bool animationStarted;
    int currentFrame;
    int currentRow;//defines the animation sequence in the sprite sheet
    int animationEnd;//defines where the nextFrame method should reset to frame 0
    QTimer *moveTimer;
    QTimer *animationTimer;
    QPixmap *bulletPic;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // BULLET_H
