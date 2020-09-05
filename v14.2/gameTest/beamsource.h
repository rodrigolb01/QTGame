#ifndef BEAMSOURCE_H
#define BEAMSOURCE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

#include "game.h"
#include "QList"
#include "enemy.h"
#include "bullet.h"
#include "eff_explosion.h"

class BeamSource : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit BeamSource(int angle=1, QObject *parent = nullptr);
    int currentFrame;
    int angle;
    QPixmap* pic;
    QTimer* t;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private slots:
    void nextFrame();
};

#endif // BEAMSOURCE_H
