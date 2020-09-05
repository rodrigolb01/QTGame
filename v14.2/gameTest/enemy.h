#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QMediaPlayer>
#include <QPainter>

//works similiar to player controlled entity, but this one is controlled by algorithms
class Enemy: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Enemy(QObject *parent=0);
    void move();
    void shoot();
    double rotateToPoint(QPointF p);
    void move_forward();

private slots:

    void nextFrame();
    void enemiesInrange();//peiodically checks if there is any enemies in it's front, if there is it will shoot periodically

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QTimer *timer;//for load the next frame of the animation
    QTimer *timer2;//for move
    QTimer *timer3;//for look for enemies
    QTimer *timer4;//for shoot in enemies
    QPixmap *spriteImage;
    int currentFrame;
    int currentSequence;
    QMediaPlayer *bullet_sound;

private:
    QList<QPointF> points;
    QPointF dest;
    int points_index;
};

#endif // ENEMY_H
