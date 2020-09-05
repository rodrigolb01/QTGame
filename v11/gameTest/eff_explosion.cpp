#include "eff_explosion.h"

extern Game* game;

EFF_Explosion::EFF_Explosion(QObject *parent) : QObject(parent)
{
    bulletPic = new QPixmap(":/images/img/beam.png");
    currentFrame=0;
    t = new QTimer;
    connect(t, &QTimer::timeout, this, &EFF_Explosion::nextFrame);
    t->start(50);

    enemy_destroyed = new QMediaPlayer;
    enemy_destroyed->setMedia(QUrl("qrc:/sounds/sounds/enemy_destroyed.wav"));
    enemy_destroyed->setVolume(10);
}

QRectF EFF_Explosion::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}

void EFF_Explosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-35,-35,*bulletPic,currentFrame,70,70,70);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void EFF_Explosion::nextFrame()
{
   currentFrame+=70;
   if(currentFrame >= 700)
   {
       if(enemy_destroyed->state() == QMediaPlayer::PlayingState)
       {
           enemy_destroyed->setPosition(0);
       }
       if(enemy_destroyed->state() == QMediaPlayer::StoppedState)
       {
           enemy_destroyed->play();
       }
       game->scene->removeItem(this);
       delete this;
       return;
   }
   this->update(boundingRect());
}
