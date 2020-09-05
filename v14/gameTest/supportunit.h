#ifndef SUPPORTUNIT_H
#define SUPPORTUNIT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QMediaPlayer>
#include <QPainter>
#include <QKeyEvent>
#include <cstdlib>
#include <set>



class SupportUnit :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit SupportUnit(QObject *parent = 0);
    ~SupportUnit();
    int currentSequence;
    int currentFrame;
    bool reverse;
    QTimer* timer;

private:

    QPixmap* spriteImage;

    QRectF boundingRect() const; //bounding area of the sprite = width x length of each sprite
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private slots:
    void nextFrame();   // Slot for loading the next frame from the sprite sheet


signals:

};

#endif // SUPPORTUNIT_H
