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

extern Game *game;

Player::Player(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    formChange=false;
    reverse = false;

    currentFrame=0; // Sets the coordinates of the current frame of the sprite
    currentSequence = 70; //starts with player facing foward (70 row)

    spriteImage = new QPixmap(":/images/img/originalT1.png"); // Load the sprite image QPixmap
    timer = new QTimer();   // Create a timer for sprite animation
    timer->start(100);   // Run the sprite on the signal generation with a frequency of 100 ms
    connect(timer, &QTimer::timeout, this, &Player::nextFrame);

    move = new QTimer();
    connect(move,&QTimer::timeout,this,&Player::pressedKeys);
    move->start(50);

    shootCooldown = new QTimer();
    connect(shootCooldown,&QTimer::timeout,this,&Player::shoot);

    MC_Cooldown = new QTimer();

    QTimer *spawnTimer = new QTimer();
    connect(spawnTimer, &QTimer::timeout,this,&Player::spawn);
    spawnTimer->start(1500);

    moveSU = new QTimer();
    moveSU->start(50);

    rotSU = new QTimer();
    rotSU->start(25);
}

void Player::keyPressEvent(QKeyEvent *event)
{
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
    if(game->scene->items().size() < 40)//max allowed of objects in screen
    {
        Enemy * enemy = new Enemy(this);
        scene()->addItem(enemy);
    }

}

void Player::shoot()
{
    if(currentWeapon==1)//beam projectile
    {
        if(info->ammo->ammo > 0)
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

            if(formChange)
            {
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
    else if(currentWeapon==2)//continuous beam shot
    {

        beam_sound = new QMediaPlayer;
        beam_sound->setMedia(QUrl("qrc:/sounds/sounds/shoot3.wav"));
        beam_sound->setVolume(10);

        BeamSource* head = new BeamSource(currentSequence);//creates beam source
        BeamSegment* tail[15];//initialize an array of segments

        for(int i=1 ;i <15; i++)
        {
            tail[i] = new BeamSegment(currentSequence);//adjust position of the tail with the head of the beam
            if(currentSequence == 700)//d
            {
                head->setPos(this->pos().x()+120, this->pos().y()+60);//postion the head and the tail
                tail[i]->setPos(head->x()+70*i,head->y()+3.8);
            }
            if(currentSequence == 560)//a
            {
                head->setPos(this->pos().x()-50, this->pos().y());//
                tail[i]->setPos(head->x()-70*i,head->y()-3.8);
            }
            if(currentSequence == 630)//w
            {
                head->setPos(this->pos().x()+70, this->pos().y()-50);//
                tail[i]->setPos(head->x()+3.8,head->y()-70*i);
            }
            if(currentSequence == 770)//s
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
            switch (currentWeapon) {
            case 1: {if(currentSequence!=70) //change angle of the sprite
                    currentSequence = 70;}break;
            case 2: {if(currentSequence!=630)
                    currentSequence = 630;}break;
            }
            if(formChange)
                if(currentSequence!=630)
                    currentSequence=630;
    }
    if(sPressed)
    {
        setPos(x(),y()+15);
        switch (currentWeapon) {
        case 1 : {if(currentSequence!= 210)
                currentSequence = 210;}break;
        case 2 : {if(currentSequence!=770)
                  currentSequence = 770;}break;
        }
        if(formChange)
            if(currentSequence!=770)
                currentSequence = 770;
    }
    if(dPressed)
    {
            setPos(x()+15,y());
            switch (currentWeapon) {
            case 1: {if(currentSequence!=140)
                    currentSequence = 140;}break;
            case 2: {if(currentSequence!=700)
                    currentSequence = 700;}break;
            }
            if(formChange)
                if(currentSequence!=700)
                    currentSequence=700;
    }
    if(aPressed)
    {
        setPos(x()-15,y());
        switch (currentWeapon) {
        case 1: {if(currentSequence!=0)
                currentSequence = 0;}break;
        case 2: {if(currentSequence!= 560)
                currentSequence = 560;}break;
        }
        if(formChange)
            if(currentSequence!=560)
                currentSequence=560;
    }

    if(spacePressed)
    {
        if(currentWeapon==1)
        {
            if(shootCooldown->isActive()==false)
            {
                shoot();
                 shootCooldown->start(500);
            }
        }
        else if(currentWeapon==2)
        {
            if(shootCooldown->isActive()==false)
            {
                shoot();
                qDebug() << "SHOOT!";
                shootCooldown->start(1200);
            }
        }
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
        if(MC_Cooldown->isActive()==false)
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

            MC_Cooldown->start(500);
        }
    }
    if(!tpressed)
    {
        MC_Cooldown->stop();
    }
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

                reverse = false;//normal flow of animation
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
            {
                currentFrame = 0;
            }
        }
    }

    this->update(-35,-35,70,70);
}

std::set<int> Player::keysPressed()
{
    return keysPressed_;
}

