#ifndef SPRITESEGMENT_H
#define SPRITESEGMENT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class SpriteSegment : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit SpriteSegment(QPixmap* picture, QObject *parent = nullptr);

    QPixmap* picture;
    int x;
    int y;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

signals:

};

#endif // SPRITESEGMENT_H
