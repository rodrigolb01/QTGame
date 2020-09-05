#ifndef INFOSHIPO_H
#define INFOSHIP_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class InfoShip : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit InfoShip(QObject *parent = nullptr);
    QPixmap *icon;
    QGraphicsTextItem *info;
private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

signals:

};

#endif // INFOSHIP_H
