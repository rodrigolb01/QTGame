#include "infoplayer.h"
#include <QRectF>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include "game.h"


InfoPlayer::InfoPlayer(QObject *parent) : QObject(parent)
{
    score = new Score;
    ammo = new Ammo;
    health = new Health;
    hpBar = new HPbar;

    icon = new QPixmap(":/images/img/msinfo1.png");
    health->hide();
    ammo->hide();
    score->hide();
    hide();
}

QRectF InfoPlayer::boundingRect() const
{
    return QRectF(-75,-150,150,300);
}

void InfoPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-75,-75, *icon, 0, 0, 150,150);
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
