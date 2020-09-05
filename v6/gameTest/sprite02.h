#ifndef SPRITE02_H
#define SPRITE02_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QPixmap>

class Sprite02 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sprite02(QObject *parent = nullptr);

signals:

private slots:
    void nextFrame(); // slot for turning images in pixmap

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    QTimer *sprite_timer02;
    QPixmap *spriteImage02;
    int currentFrame_spr02;
};
#endif // SPRITE02_H
