#include "player.h"
#include <QBitmap>
#include "bullet.h"
#include "game.h"
#include "enemy.h"
#include "stationaryObject.h"
#include <QLineF>
#include <typeinfo>


extern Game *game;

Player::Player(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    currentFrame=0; // Sets the coordinates of the current frame of the sprite
    spriteImage = new QPixmap(":/images/img/spritesheet01d.png"); // Load the sprite image QPixmap
    timer = new QTimer();   // Create a timer for sprite animation
    timer->start(100);   // Run the sprite on the signal generation with a frequency of 100 ms
    currentAngle = 70;
    connect(timer, &QTimer::timeout, this, &Player::nextFrame);

    moveTimer = new QTimer();
    connect(moveTimer,&QTimer::timeout,this,&Player::pressedKeys);
    moveTimer->start(50);

    shootCooldown = new QTimer();
    connect(shootCooldown,&QTimer::timeout,this,&Player::shoot);

    QTimer *spawnTimer = new QTimer();
    connect(spawnTimer, &QTimer::timeout,this,&Player::spawn);
    spawnTimer->start(1000);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        currentAngle = 70;
    }
    if(event->key() == Qt::Key_D)
    {
        currentAngle = 140;
    }
    if(event->key() == Qt::Key_A)
    {
        currentAngle = 0;
    }
    if(event->key() == Qt::Key_S)
    {
        currentAngle = 210;
    }

    keysPressed_.insert(event->key());
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    keysPressed_.erase(event->key());
}

QRectF Player::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}

bool Player::playerCollidesWith(QGraphicsItem *item)
{
    QList<QGraphicsItem*> colliding_Items = collidingItems();
    for(size_t i=0, n=colliding_Items.size(); i<n; i++)
    {
        if(typeid (*(colliding_Items[i])) == typeid(*item))
        {
            return true;
        }
    }
    return false;
}

bool Player::playerCollidesWithEnemy()
{
    QList<QGraphicsItem*> colliding_Items = collidingItems();
    for(size_t i=0, n=colliding_Items.size(); i<n; i++)
    {
        if(typeid (*(colliding_Items[i])) == typeid(Enemy))
        {
            return true;
        }
    }
    return false;
}

void Player::spawn()
{
    if(game->scene->items().size() < 40)//max allowed of objects in screen
    {
        Enemy * enemy = new Enemy();
        scene()->addItem(enemy);
    }

}

void Player::shoot()
{
    if(info->ammo->ammo > 0)
    {
        bullet_sound = new QMediaPlayer();
        bullet_sound->setMedia((QUrl("qrc:/sounds/sounds/shoot2.wav")));
        bullet_sound->setVolume(20);

        Bullet * bullet = new Bullet(0,currentAngle,50,1);


        //bullet spawnpoint adjustments
        if(currentAngle == 140)
        {
            bullet->setPos(this->pos().x(), this->pos().y()-10);//minimum distance that the bullet can spawn withou collide with player
        }
        if(currentAngle == 0)
        {
            bullet->setPos(this->pos().x()-150, this->pos().y()-10);//
        }
        if(currentAngle == 70)
        {
            bullet->setPos(this->pos().x(), this->pos().y()-80);//
        }
        if(currentAngle == 210)
        {
            bullet->setPos(this->pos().x(), this->pos().y()+35);//
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
        info->ammo->decrease();
    }
}

void Player::reload()
{
    reload_sound = new QMediaPlayer();
    reload_sound->setMedia(QUrl("qrc:/sounds/sounds/reload1.wav"));
    reload_sound->setVolume(20);

    if(reload_sound->state() == QMediaPlayer::PlayingState)
    {
        reload_sound->setPosition(0);
    }
    else if(reload_sound->state() == QMediaPlayer::StoppedState)
    {
        reload_sound->play();
    }

    for(size_t i=info->ammo->ammo; i<10; i++)
    {
        info->ammo->increase();
    }
}

void Player::pressedKeys()
{
    bool wPressed = keysPressed().count(Qt::Key_W);
    bool sPressed = keysPressed().count(Qt::Key_S);
    bool dPressed = keysPressed().count(Qt::Key_D);
    bool aPressed = keysPressed().count(Qt::Key_A);
    bool spacePressed = keysPressed().count(Qt::Key_Space);
    bool rPressed = keysPressed().count(Qt::Key_R);
    /*************************collisions handling*********************************
     * before change the position, temp stores the previous position of the player.
     * If this new position inflics in another object bounding area, so it will be reseted to the previous position.
     */
    QPointF temp = QPointF(pos());

    if(wPressed)
    {
            setPos(x(),y()-15);
            if(playerCollidesWith(game->w))
                emit(thrustsObject(70));
    }
    if(sPressed)
    {
            setPos(x(),y()+15);
            if(playerCollidesWith(game->w))
                emit(thrustsObject(210));
    }
    if(dPressed)
    {
            setPos(x()+15,y());
            if(playerCollidesWith(game->w))
                emit(thrustsObject(140));
    }
    if(aPressed)
    {
            setPos(x()-15,y());
            if(playerCollidesWith(game->w))
                emit(thrustsObject(0));
    }
    if(playerCollidesWith(game->mothership1) || playerCollidesWithEnemy())
    {
        setPos(temp);
    }

    if(spacePressed)
    {
        if(!shootCooldown->isActive())
            shoot();
             shootCooldown->start(300);
    }
    else if(!spacePressed)
    {
        shootCooldown->stop();
    }
    if(rPressed)
    {
        weaponReload = new QTimer();
        weaponReload->singleShot(1000,this,SLOT(reload()));
        weaponReload->start();
    }
}


void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void Player::nextFrame()
{
    /* At a signal from the timer 20 to move the point of rendering pixels
     * If currentFrame = 300 then zero out it as sprite sheet size of 300 pixels by 20
     * */
    currentFrame += 70;
    if (currentFrame >= 210)
        currentFrame = 0;
    this->update(-35,-35,70,70);
}

std::set<int> Player::keysPressed()
{
    return keysPressed_;
}

