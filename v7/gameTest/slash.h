#ifndef SLASH_H
#define SLASH_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QMediaPlayer>
#include <QPainter>

class slash : public QObject
{
    Q_OBJECT
public:
    explicit slash(QObject *parent = nullptr);
    bool friendlyFire;

private slots:
    void nextFrame();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect();

    QTimer *timer;
    QPixmap *spriteImage;
    int angle;
    int currentFrame;
    QMediaPlayer *beamSlash_Sound;

};

#endif // SLASH_H
