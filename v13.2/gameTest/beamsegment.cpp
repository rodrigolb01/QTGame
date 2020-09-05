#include "beamsegment.h"

extern Game* game;

BeamSegment::BeamSegment(int angle, QObject *parent) : QObject(parent)
{
    this->angle = angle;
    pic = new QPixmap(":/images/img/beams.png");
    currentFrame=0;

    setTransformOriginPoint(-35,-35);
    switch (angle) {
    case (70): setRotation(90);break;
    case (210): setRotation(270);break;
    case (140):   setRotation(180);break;
    }
    t = new QTimer(this);
    connect(t,&QTimer::timeout,this,&BeamSegment::nextFrame);
    t->start(50);
}

void BeamSegment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-35,-35, *pic, currentFrame, 70, 70,70);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF BeamSegment::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}

void BeamSegment::nextFrame()
{
    currentFrame += 70;
    if (currentFrame >= 910)
    {
        //check if collides with any target, if does, destroy it
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for(int i=0; i<colliding_items.size(); i++)
        {
            if(typeid (*(colliding_items[i]))== typeid (Enemy) || typeid (*(colliding_items[i]))== typeid (Bullet) )
            {
                EFF_Explosion *e = new EFF_Explosion();//creates explosion
                e->setPos(colliding_items[i]->pos());
                game->scene->addItem(e);
                game->scene->removeItem(colliding_items[i]);//delete the target
                delete(colliding_items[i]);
            }
        }

        game->scene->removeItem(this);
        delete this;
        return;
    }
    this->update(-35,-35,70,70);
}


