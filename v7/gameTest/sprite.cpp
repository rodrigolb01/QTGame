#include "sprite.h"
#include <QBitmap>
#include "bullet.h"
#include "game.h"
#include "spritee.h"

extern Game *game;


Sprite::Sprite(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    currentFrame=0; // Sets the coordinates of the current frame of the sprite
    spriteImage = new QPixmap(":/images/img/spritesheet01d.png"); // Load the sprite image QPixmap
    timer = new QTimer();   // Create a timer for sprite animation
    timer->start(100);   // Run the sprite on the signal generation with a frequency of 100 ms
    currentAngle = 70;
    connect(timer, &QTimer::timeout, this, &Sprite::nextFrame);

}

void Sprite::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        currentAngle = 70;
        setPos(x(),y()-10);
    }
    if(event->key() == Qt::Key_D)
    {
        currentAngle = 140;
        setPos(x()+10,y());
    }
    if(event->key() == Qt::Key_A)
    {
        currentAngle = 0;
        setPos(x()-10,y());
    }
    if(event->key() == Qt::Key_S)
    {
        currentAngle = 210;
        setPos(x(),y()+10);
    }

    if(event->key() == Qt::Key_Space)
    {
        bullet_sound = new QMediaPlayer();
        bullet_sound->setMedia((QUrl("qrc:/sounds/sounds/shoot2.wav")));
        bullet_sound->setVolume(20);

        Bullet * bullet = new Bullet(0,currentAngle);
        bullet->friendlyFire = true;

        //bullet spawnpoint adjustments
        if(currentAngle == 140)
        {
            bullet->setPos(this->pos().x()+50, this->pos().y()-40);//minimum distance that the bullet can spawn withou collide with player
        }
        if(currentAngle == 0)
        {
            bullet->setPos(this->pos().x()-110, this->pos().y()-40);//
        }
        if(currentAngle == 70)
        {
            bullet->setPos(this->pos().x()-30, this->pos().y()-120);//
        }
        if(currentAngle == 210)
        {
            bullet->setPos(this->pos().x() -30, this->pos().y()+35);//
        }

        scene()->addItem(bullet);
        // play bullet_sound
        if(bullet_sound->state() == QMediaPlayer::PlayingState)
        {
            bullet_sound->setPosition(0);
        }
        else if(bullet_sound->state() == QMediaPlayer::StoppedState)
        {
            bullet_sound->play();
        }
    }
}

void Sprite::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
    }
    if(event->key() == Qt::Key_D)
    {
    }
    if(event->key() == Qt::Key_W)
    {
    }
    if(event->key() == Qt::Key_S)
    {
    }
}

QRectF Sprite::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}

void Sprite::spawn()
{
    if(game->scene->items().size() < 20)//max allowed of objects in screen
    {
        spriteE * enemy = new spriteE();
        scene()->addItem(enemy);
    }

}


void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* In the graphic renderer we draw the sprite
     * The first two arguments - is the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By setting the X coordinate with the variable currentFrame we would like to move the camera on the sprite
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
    painter->drawPixmap(-35,-35, *spriteImage, currentFrame, currentAngle, 70,70);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Sprite::nextFrame()
{
    /* At a signal from the timer 20 to move the point of rendering pixels
     * If currentFrame = 300 then zero out it as sprite sheet size of 300 pixels by 20
     * */
    currentFrame += 70;
    if (currentFrame >= 210)
        currentFrame = 0;
    this->update(-35,-35,70,70);
}
