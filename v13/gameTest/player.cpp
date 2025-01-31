#include "player.h"
#include <QBitmap>
#include <qmath.h>
#include "bullet.h"
#include "beamsource.h"
#include "beamsegment.h"
#include "game.h"
#include "enemy.h"
#include "stationaryObject.h"
#include <QLineF>
#include <typeinfo>
#include <QMetaObject>

extern Game *game;

Player::Player(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    formChange=false;
    reverse = false;

    currentFrame=0; // Sets the coordinates of the current frame of the sprite
    currentSequence = 70; //starts with player facing foward (row 70 px - Y axis)

    spriteImage = new QPixmap(":/images/img/originalT1.png"); // Load the sprite sheet with QPixmap
    timer = new QTimer(this);   // Create a timer for sprite animation
    timer->start(100);   // Run the sprite on the signal generation with a frequency of 100 ms
    connect(timer, &QTimer::timeout, this, &Player::nextFrame);
    //gets the keys pressed my the player periodically and handle them
    getKeys = new QTimer(this);
    connect(getKeys,&QTimer::timeout,this,&Player::pressedKeys);
    getKeys->start(50);

    shootCooldown = new QTimer(this);//define cooldown timer for consecultive shoots
    connect(shootCooldown,&QTimer::timeout,this,&Player::shoot);

    FC_cooldown = new QTimer(this);//define cooldown timer for consecultive form changes (transformation)

    QTimer *spawnTimer = new QTimer(this);//define cooldown for Enemy spawning
    connect(spawnTimer, &QTimer::timeout,this,&Player::spawn);
    spawnTimer->start(1000);

    moveSU = new QTimer(this);//define timer for moving Support Unit
    moveSU->start(50);

    rotSU = new QTimer(this);
    rotSU->start(25);

    segD = new SpriteSegment(spriteImage, this);
    segU = new SpriteSegment(spriteImage, this);
    segL = new SpriteSegment(spriteImage, this);
    segR = new SpriteSegment(spriteImage, this);

    QTimer* cmp = new QTimer(this);
    connect(cmp, &QTimer::timeout, this, &Player::complement);
    cmp->start(10);

    currentSequence+=560;//change the appearance of the player to upper body of the robot
    s = new SupportUnit(this);//create support unit
    s->setPos(pos());
    s->currentSequence = currentSequence -280;//set support unit to be the lower body
    setZValue(2);
    s->setZValue(1);//position the support unit under the player(where the legs should be)
    formChange = true;//flag uncombined

    connect(moveSU, &QTimer::timeout, this, &Player::moveSUforward);
    connect(rotSU, &QTimer::timeout, this, &Player::rotateSUtoPoint);

     FC_cooldown->start(500);
}

void Player::keyPressEvent(QKeyEvent *event)//get the keys pressed
{
    keysPressed_.insert(event->key());
}

void Player::keyReleaseEvent(QKeyEvent *event)//get the keys released
{
    keysPressed_.erase(event->key());
}

QRectF Player::boundingRect() const// bound of the object area
{
    return QRectF(-35,-35,70,70);
}

bool Player::playerCollidesWith(QGraphicsItem *item) //handling of collision between objects
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

bool Player::playerCollidesWithEnemy()//handling collision with enemy
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

int Player::getLenght() //unused
{
    QLineF* l;
    switch (currentSequence) {
    case 770: l = new QLineF(pos(), QPointF(x(),game->scene->height()));break;//down
    case 630: l = new QLineF(pos(), QPointF(x(),0));break;//up
    case 700: l = new QLineF(QPointF(game->scene->width(),y()), pos());break;//right
    case 560: l = new QLineF(QPoint(0,y()), pos());break;//left
    }
    return l->length()/70;
}

void Player::spawn()
{
    if(game->scene->items().size()< 30)//max allowed of enemies in screen
    {
        Enemy * enemy = new Enemy(this);
        scene()->addItem(enemy);
    }

}

void Player::shoot()
{
    if(info->ammo->ammo > 0)
    {
        if(formChange) //if its in spacecraft form, the shoot will be a projectile
        {
            bullet_sound = new QMediaPlayer();
            bullet_sound->setMedia((QUrl("qrc:/sounds/sounds/shoot2.wav")));
            bullet_sound->setVolume(10);

            Bullet * bullet = new Bullet(0,currentSequence,50,1);

            //bullet spawnpoint adjustments
            if(currentSequence == 140 || currentSequence == 700 || currentSequence == 420)
            {
                bullet->setPos(this->pos().x(), this->pos().y()-20);//minimum distance that the bullet can spawn withou collide with player
            }
            if(currentSequence == 0 || currentSequence == 560 || currentSequence == 280)
            {
                bullet->setPos(this->pos().x()-140, this->pos().y()-20);//
            }
            if(currentSequence == 70 || currentSequence == 630 || currentSequence == 350)
            {
                bullet->setPos(this->pos().x()+12, this->pos().y()-60);//
            }
            if(currentSequence == 210 || currentSequence == 770 || currentSequence == 490 )
            {
                bullet->setPos(this->pos().x()-12, this->pos().y()+20);//
            }

            //creating the support unit bullet

            Bullet * bullet2 = new Bullet(0, currentSequence,50, 1);

            if(currentSequence == 140 || currentSequence == 700 || currentSequence == 420)
            {
                bullet2->setPos(this->pos().x(), this->pos().y()+30);//minimum distance that the bullet can spawn withou collide with player
            }
            if(currentSequence == 0 || currentSequence == 560 || currentSequence == 280)
            {
                bullet2->setPos(this->pos().x()-140, this->pos().y()+30);//
            }
            if(currentSequence == 70 || currentSequence == 630 || currentSequence == 350)
            {
                bullet2->setPos(this->pos().x()-12, this->pos().y()-60);//
            }
            if(currentSequence == 210 || currentSequence == 770 || currentSequence == 490 )
            {
                bullet2->setPos(this->pos().x()+12, this->pos().y()+20);//
            }
            scene()->addItem(bullet2);

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
        /* if its in humaniod form the shoot will be a beam.
         * An beam is composed by head(source) and tail(segments).
         * The head will have enough segments to reach something that limits the beam lenght,(E.g. an large object, the map bounds...)
         */
        else
        {

            beam_sound = new QMediaPlayer;
            beam_sound->setMedia(QUrl("qrc:/sounds/sounds/shoot3.wav"));
            beam_sound->setVolume(10);

            BeamSource* head = new BeamSource(currentSequence,this);//creates beam source
            BeamSegment* tail[15];//initialize an array of segments

            for(int i=1 ;i <15; i++)
            {
                tail[i] = new BeamSegment(currentSequence,this);//adjust position of the tail with the head of the beam
                if(currentSequence == 140)//d
                {
                    head->setPos(this->pos().x()+120, this->pos().y()+60);//postion the head and the tail
                    tail[i]->setPos(head->x()+70*i,head->y()+3.8);
                }
                if(currentSequence == 0)//a
                {
                    head->setPos(this->pos().x()-50, this->pos().y());//
                    tail[i]->setPos(head->x()-70*i,head->y()-3.8);
                }
                if(currentSequence == 70)//w
                {
                    head->setPos(this->pos().x()+70, this->pos().y()-50);//
                    tail[i]->setPos(head->x()+3.8,head->y()-70*i);
                }
                if(currentSequence == 210)//s
                {
                    head->setPos(this->pos().x()+5, this->pos().y()+120);//
                    tail[i]->setPos(head->x()-3.8,head->y()+70*i);
                }
                game->scene->addItem(tail[i]);
            }
            game->scene->addItem(head);
            if(beam_sound->state() == QMediaPlayer::PlayingState)
            {
                beam_sound->setPosition(0);
            }
            if(beam_sound->state() == QMediaPlayer::StoppedState)
            {
                beam_sound->play();
            }
        }
    }

}


void Player::pressedKeys()
{
    qInfo() << "items on screen: " << scene()->items().size();
    bool wPressed = keysPressed().count(Qt::Key_W);
    bool sPressed = keysPressed().count(Qt::Key_S);
    bool dPressed = keysPressed().count(Qt::Key_D);
    bool aPressed = keysPressed().count(Qt::Key_A);
    bool spacePressed = keysPressed().count(Qt::Key_Space);
    bool pressed1 = keysPressed().count(Qt::Key_1);
    bool pressed2 = keysPressed().count(Qt::Key_2);
    bool tpressed = keysPressed().count(Qt::Key_T);
    /*************************collisions handling*********************************
     * before change the position, temp stores the previous position of the player.
     * If this new position inflics in another object bounding area, so it will be reseted to the previous position.
     */
    QPointF temp = QPointF(pos());

    if(wPressed)
    {
            setPos(x(),y()-15); //move

            if(formChange)
            {
                if(currentSequence!=630)
                    currentSequence=630;
            }
            else
            {
                if(currentSequence!=70) //change angle of the sprite
                    currentSequence = 70;
            }
    }
    if(sPressed)
    {
        setPos(x(),y()+15);

        if(formChange)
        {
            if(currentSequence!=770)
                currentSequence = 770;
        }
        else
        {
            if(currentSequence!= 210)
                currentSequence = 210;
        }
    }
    if(dPressed)
    {
            setPos(x()+15,y());

            if(formChange)
            {
                if(currentSequence!=700)
                    currentSequence=700;
            }
            else
            {
                if(currentSequence!=140)
                   currentSequence = 140;
            }
    }
    if(aPressed)
    {
        setPos(x()-15,y());

        if(formChange)
        {
            if(currentSequence!=560)
                currentSequence=560;
        }
        else
        {
            if(currentSequence!=0)
                currentSequence = 0;
        }
    }

    if(spacePressed)
    {
        if(shootCooldown->isActive()==false)
        {
            shoot();

            if(!formChange)
                shootCooldown->start(500);

            else
                shootCooldown->start(1200);//more cooldown for the large beam
        }
    }
    else if(!spacePressed)
    {
        shootCooldown->stop();
    }
    if(pressed2)
    {
        currentWeapon = 2;
    }
    if(pressed1)
    {
        currentWeapon = 1;
    }

    //collision behavior
    if(playerCollidesWith(game->mothership1) || playerCollidesWithEnemy())
    {
        setPos(temp);
    }

    /*
     * if the player is "combined with the SupportUnit, it will "separate" them by creating
     * a SupportUnit as the lower body of the robot, and the player sprite became the upper body.
     *
     * If they arent, we wanna just play the SupportUnit and player animations backwards and delete
     * the supportUnit when it reaches the end, giving the illusion they are combined in one object.
     */
    if(tpressed)
    {
        if(FC_cooldown->isActive()==false)
        {
            if(formChange == false)// if player is "combined with support unit"
            {
                currentSequence+=560;//change the appearance of the player to upper body of the robot
                s = new SupportUnit(this);//create support unit
                s->setPos(pos());
                s->currentSequence = currentSequence -280;//set support unit to be the lower body
                setZValue(2);
                s->setZValue(1);//position the support unit under the player(where the legs should be)
                game->scene->addItem(s);
                formChange = true;//flag uncombined

                connect(moveSU, &QTimer::timeout, this, &Player::moveSUforward);
                connect(rotSU, &QTimer::timeout, this, &Player::rotateSUtoPoint);

            }
            else//if they are separated
            {
                //reverse flow of the animation
                s->reverse=true;
                reverse = true;

                s->currentFrame = 210;//starts with the last frame
                currentFrame = 210;

                timer->start(100);
                s->timer->start(100);

                disconnect(moveSU, &QTimer::timeout, this, &Player::moveSUforward);
                disconnect(rotSU, &QTimer::timeout, this, &Player::rotateSUtoPoint);

          }

            FC_cooldown->start(500);
        }
    }
    if(!tpressed)
    {
        FC_cooldown->stop();
    }

    segU->setPos(x(),y()-70);
    segD->setPos(x(),y()+70);
    segR->setPos(x()+70,y());
    segL->setPos(x()-70,y());
}

void Player::moveSUforward()
{
    int STEP_SIZE = 1;
        double theta = rotation(); // degrees

        double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
        double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

        s->setPos(x()+dx, y()+dy + 25);
}

void Player::rotateSUtoPoint()
{
    QPointF p = pos();
    s->currentSequence = currentSequence-280;
    setRotation(-1* QLineF(pos(),p).angle());
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
    painter->drawPixmap(-35,-35, *spriteImage, currentFrame, currentSequence, 70,70);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Player::nextFrame()
{
    if(reverse)
    {
        currentFrame -= 70;
        if(currentFrame <=0)
        {
            if(formChange)
            {
                currentFrame = 0;
                currentSequence-=560;//return the player appearance to the entire robot.

                reverse = false;//return to normal flow of the animation
                formChange = false;
            }
        }
    }
    else
    {
        currentFrame += 70;
        if (currentFrame >= 210)
        {

            if(formChange)
            {
                currentFrame = 210;
                timer->stop();
            }
            else
                currentFrame = 0;
        }

    }

    this->update(-35,-35,70,70);
}

void Player::complement()
{
    if(currentSequence==70) //forward
    {

        segR->x=70;
        segR->y=840;
        segL->y=840;
        segL->x=350;
    }
    if(currentSequence==210)//back
    {

        segR->x=70;
        segR->y=840;
        segL->x=350;
        segL->y=840;
    }
    if(currentSequence == 630)
    {
        if(currentFrame == 0)
        {

            segR->x=70;
            segR->y=840;
            segL->y=840;
            segL->x=350;
        }
        if(currentFrame == 70)
        {

            segR->x=140;
            segR->y=840;
            segL->y=840;
            segL->x=420;
        }
        if(currentFrame == 140)
        {
            segU->x=280;
            segU->y=770;
            segR->x=210;
            segR->y=840;
            segL->y=840;
            segL->x=490;
        }
        if(currentFrame ==210)
        {
            segR->x=280;
            segR->y=840;
            segL->y=770;
            segL->x=490;
        }

    }

    if(currentSequence==770)//forward
    {
        if(currentFrame == 0)
        {

            segR->x=70;
            segR->y=840;
        }
        if(currentFrame == 70)
        {
            segR->x=560;//empty
            segR->y=910;//empty
        }
        if(currentFrame == 140)
        {

            segR->x=280;
            segR->y=910;
            segL->x=420;
            segL->y=770;
        }
        if(currentFrame ==210)
        {

            segR->x=420;
            segR->y=910;
            segL->x=490;
            segL->y=910;
        }
   }
    if(currentSequence== 560 || currentSequence ==700)
    {
        if(currentFrame==210)
        {//clear
            segU->x=0;
            segU->y=980;
            segD->x=0;
            segD->y=980;
            segL->x=0;
            segL->y=980;
            segR->x=0;
            segR->y=980;
        }
    }
    //the sides dont need any complements
    if(  currentSequence == 0 || currentSequence==140)
    {//clear all the segments with empty spaces
        segU->x=0;
        segU->y=980;
        segD->x=0;
        segD->y=980;
        segL->x=0;
        segL->y=980;
        segR->x=0;
        segR->y=980;
    }
}

std::set<int> Player::keysPressed()
{
    return keysPressed_;
}

