#ifndef SPRITE01_H
#define SPRITE01_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QPixmap>

class Sprite01 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sprite01(QObject *parent = nullptr);

signals:

private slots:
    void nextFrame(); // slot for turning images in pixmap

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    QTimer *sprite_timer01;
    QPixmap *spriteImage01;
    int currentFrame_spr01;
};

#endif // SPRITE01_H
