#ifndef SPRITESHIP_H
#define SPRITESHIP_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QMediaPlayer>
#include <QPainter>
#include <spritee.h>

class spriteship : spriteE
{
    Q_OBJECT
public:
    explicit spriteship(QObject *parent = nullptr);

signals:

private slots:
    void spawn();

};

#endif // SPRITESHIP_H
