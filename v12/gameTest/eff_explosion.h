#ifndef EFF_EXPLOSION_H
#define EFF_EXPLOSION_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include "game.h"
#include <QMediaPlayer>

class EFF_Explosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit EFF_Explosion(QObject *parent = nullptr);
private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int currentFrame;
    QTimer *t;
    QTimer *animationTimer;
    QPixmap *bulletPic;
    QMediaPlayer *enemy_destroyed;

private slots:
    void nextFrame();
};

#endif // EFF_EXPLOSION_H
