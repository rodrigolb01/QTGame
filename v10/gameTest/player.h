#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QMediaPlayer>
#include <QPainter>
#include <QKeyEvent>
#include <cstdlib>
#include <set>
#include "infoplayer.h"


//symbolizes an entitie controlable by the player.
class Player : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    InfoPlayer *info;

    void keyPressEvent(QKeyEvent * event); // controls
    void keyReleaseEvent(QKeyEvent *event);

    std::set<int> keysPressed();
    QRectF boundingRect() const; //bounding area of the sprite = width x length of each sprite


private slots:
    void nextFrame();   // Slot for loading the next frame from the sprite sheet

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //painter class to render the sprites

    std::set<int> keysPressed_; //keyboardMapping

    QTimer *timer;      // Timer for turning images into QPixmap
    QTimer *moveTimer;
    QTimer *shootCooldown;
    QTimer *weaponReload;
    QPixmap *spriteImage;  // In this QPixmap object will be placed the sprite sheet
    QMediaPlayer *bullet_sound; // Sound effect
    QMediaPlayer *reload_sound;


    int currentFrame;   // Coordinate X, which starts the next frame of the sprite row
    int currentAngle;   // Coordinate Y, which determine witch row we are
    bool playerCollidesWith(QGraphicsItem *item);
    bool playerCollidesWithEnemy();

public slots:
    void spawn(); //the player entities creates enemies
    void shoot();
    void reload();
    void pressedKeys(); //move player with keyboard keys
signals:
    void thrustsObject(int direction);
};

#endif // PLAYER_H
