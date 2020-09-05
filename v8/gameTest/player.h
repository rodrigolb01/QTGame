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


//symbolizes an entitie controlable by the player.
class Player : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    void keyPressEvent(QKeyEvent * event); // controls
    void keyReleaseEvent(QKeyEvent *event);

    std::set<int> keysPressed();

private slots:
    void nextFrame();   // Slot for loading the next frame from the sprite sheet

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //painter class to render the sprites
    QRectF boundingRect() const; //bounding area of the sprite = width x length of each sprite

    std::set<int> keysPressed_;

    QTimer *timer;      // Timer for turning images into QPixmap
    QTimer *moveTimer;
    QTimer *timerAnim;     //Timer for start animation
    QTimer *shootCooldown;
    QPixmap *spriteImage;  // In this QPixmap object will be placed the sprite sheet
    int currentFrame;   // Coordinate X, which starts the next frame of the sprite row
    int currentAngle;   // Coordinate Y, which determine witch row we are
    QMediaPlayer *bullet_sound; // Sound effect
public slots:
    void spawn(); //the player entities creates enemies
    void shoot();
    void moveStep_(); //move player with keyboard keys
    void startAnimation();
signals:
    void keyPressed(int key);
    void keyReleased(int key);

};

#endif // PLAYER_H
