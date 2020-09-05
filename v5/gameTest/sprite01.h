#ifndef SPRITE01_H
#define SPRITE01_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Sprite01 : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sprite01(QObject *parent = 0);

signals:

public slots:

private slots:
    void nextFrame();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    QTimer *sprite01_timer;
    QPixmap *sprite01_image;
    int sprite01_currentFrame;
};

#endif // SPRITE01_H
