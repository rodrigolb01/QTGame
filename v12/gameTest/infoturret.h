#ifndef INFOTURRET_H
#define INFOTURRET_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "hpbar.h"

//class that holds information about an turret
class InfoTurret : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit InfoTurret(QObject *parent = nullptr);
    HPbar *hpBar;
    QPixmap *icon;
    QGraphicsTextItem *info;
private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // INFOTURRET_H
