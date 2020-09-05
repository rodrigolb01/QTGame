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
#include "supportunit.h"
#include "spritesegment.h"



//symbolizes an entitie controlable by the player.
class Player : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    InfoPlayer *info;
    SupportUnit* s;

    //if the current sprite does not fit in the bounding rect it will be complemented other pieces of the sprite
    SpriteSegment* segR;
    SpriteSegment* segL;
    SpriteSegment* segU;
    SpriteSegment* segD;

    void keyPressEvent(QKeyEvent * event); // controls
    void keyReleaseEvent(QKeyEvent *event);

    std::set<int> keysPressed();
    QRectF boundingRect() const; //bounding area of the sprite = width x length of each sprite7


private slots:
    void nextFrame();   // Slot for loading the next frame from the sprite sheet
    void complement(); //Slot for adding other pieces of the sprite

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //painter class to render the sprites

    std::set<int> keysPressed_; //keyboardMapping

    QTimer *timer;      // Timer for turning images into QPixmap
    QTimer *getKeys;
    QTimer *moveSU;
    QTimer *rotSU;
    QTimer *shootCooldown;
    QTimer *FC_cooldown;
    QPixmap *spriteImage;  // In this QPixmap object will be placed the sprite sheet
    QMediaPlayer *bullet_sound; // Sound effect
    QMediaPlayer *beam_sound;

    int currentFrame;   // Coordinate X, which starts the next frame of the sprite row
    int currentSequence;   // Coordinate Y, which determine witch row we are

    int currentWeapon = 1; // sets the block of animations based on wich weapon is the player holding at the moment
    bool playerCollidesWith(QGraphicsItem *item);
    bool playerCollidesWithEnemy();
    bool formChange; // true if the player changed form
    bool reverse; // true if the animation should be played backwards (E.g transforming back to jet)
    int getLenght();//gets the distance betweeen current pos and bound of the scene

private slots:
    void spawn(); //the player entitie creates enemies
    void shoot(); //the player entitie create bullets
    void pressedKeys(); //move player with keyboard keys
    void moveSUforward(); //move the Support Unit towards the player
    void rotateSUtoPoint(); // rotate the Support Unit towards the player
signals:
    void thrustsObject(int direction);//(Unused)
private:

};

#endif // PLAYER_H
