#ifndef BEAMSEGMENT_H
#define BEAMSEGMENT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

#include "game.h"
#include "enemy.h"
#include "bullet.h"
#include "eff_explosion.h"

class BeamSegment : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit BeamSegment(int angle=1, QObject *parent = nullptr);
    int currentFrame;
    int angle;
    QPixmap* pic;
    QTimer* t;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
public slots:
    void nextFrame();

};

#endif // BEAMSEGMENT_H
