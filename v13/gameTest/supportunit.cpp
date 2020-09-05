#include "supportunit.h"

SupportUnit::SupportUnit(QObject *parent)
{
    timer = new QTimer(this);
    currentFrame = 70;
    spriteImage = new QPixmap(":/images/img/originalT1.png");
    reverse=false;
    connect(timer, &QTimer::timeout, this, &SupportUnit::nextFrame);
    timer->start(100);
}

SupportUnit::~SupportUnit()
{
}

QRectF SupportUnit::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}

void SupportUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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


void SupportUnit::nextFrame()
{
    if(reverse)
    {
        currentFrame -=70;
        if(currentFrame < 70)
        {
            timer->stop();
            delete this;
            return;
        }
    }

    else
    {
        currentFrame += 70;
        if (currentFrame >= 210)
        {
            timer->stop();
        }
    }

    this->update(-35,-35,70,70);
}
