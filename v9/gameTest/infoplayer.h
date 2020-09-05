#ifndef INFOPLAYER_H
#define INFOPLAYER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "score.h"
#include "health.h"
#include "ammo.h"
#include "hpbar.h"

class InfoPlayer : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit InfoPlayer(QObject *parent = nullptr);
    QPixmap* icon;
    Score* score;
    Health* health;
    Ammo* ammo;
    HPbar* hpBar;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

signals:

};

#endif // INFOPLAYER_H
