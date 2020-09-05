#include "beamsource.h"

extern Game* game;

BeamSource::BeamSource(int angle, QObject *parent) : QObject(parent)
{
    this->angle = angle;
    pic = new QPixmap(":/images/img/beams.png");
    currentFrame=0;

    setTransformOriginPoint(-35,-35);
    switch (angle) {
    case (630): setRotation(90);break;
    case (770): setRotation(270);break;
    case (700):   setRotation(180);break;
    }
    t = new QTimer;
    connect(t,&QTimer::timeout,this,&BeamSource::nextFrame);
    //connect(t,&QTimer::timeout,tail,&BeamSegment::nextFrame);
    t->start(50);
}

QRectF BeamSource::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}

void BeamSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-35,-35, *pic, currentFrame, 0, 70,70);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void BeamSource::nextFrame()
{
    currentFrame += 70;
    if (currentFrame >= 910)
    {
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for(int i=0; i<colliding_items.size(); i++)
        {
            if(typeid (*(colliding_items[i]))== typeid (Enemy) || typeid (*(colliding_items[i]))== typeid (Bullet) )
            {
                game->scene->removeItem(colliding_items[i]);
                delete(colliding_items[i]);
                if(typeid (*(colliding_items[i])) == typeid (Enemy))
                    game->player1->info->score->increase();
            }

        }
        game->scene->removeItem(this);
        delete this;
        return;
    }
    this->update(-35,-35,70,70);
}
