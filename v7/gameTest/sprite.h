#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QMediaPlayer>
#include <QPainter>
#include <QKeyEvent>


//symbolizes an entitie controlable by the player.
class Sprite : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sprite(QObject *parent = 0);
    void keyPressEvent(QKeyEvent * event); // controls
    void keyReleaseEvent(QKeyEvent *event);


private slots:
    void nextFrame();   // Slot for loading the next frame from the sprite sheet

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //painter class to render the sprites
    QRectF boundingRect() const; //bounding area of the sprite = width x length of each sprite

    QTimer *timer;      // Timer for turning images into QPixmap
    QPixmap *spriteImage;   // In this QPixmap object will be placed the sprite sheet
    int currentFrame;   // Coordinate X, which starts the next frame of the sprite row
    int currentAngle;   // Coordinate Y, which determine witch row we are
    QMediaPlayer *bullet_sound; // Sound effect
public slots:
    void spawn(); //the player entities creates enemies

};

#endif // SPRITE_H
