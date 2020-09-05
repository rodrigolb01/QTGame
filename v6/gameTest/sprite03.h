#ifndef SPRITE03_H
#define SPRITE03_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QPixmap>

class Sprite03 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sprite03(QObject *parent = nullptr);

signals:

private slots:
    void nextFrame(); // slot for turning images in pixmap

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    QTimer *sprite_timer03;
    QPixmap *spriteImage03;
    int currentFrame_spr03;
};
#endif // SPRITE03_H
