#ifndef STATIONARYOBJECT_H
#define STATIONARYOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QMediaPlayer>
#include <QPainter>
#include <QPolygonF>

class StationaryObject : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit StationaryObject(QObject *parent = nullptr);
    QGraphicsPolygonItem *boundingPolygon;
public slots:
    void move(int direction);

private:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QPixmap *spriteImage;
};

#endif // STATIONARYOBJECT_H
