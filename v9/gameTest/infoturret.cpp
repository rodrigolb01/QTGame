#include "infoturret.h"
#include <QBrush>
#include <QPainter>
#include <QFont>

InfoTurret::InfoTurret(QObject *parent) : QObject(parent)
{
    icon = new QPixmap(":/images/img/beamTurret1.png");
    hpBar = new HPbar;
    info = new QGraphicsTextItem();
    info->setPos(pos());
    info->setFont(QFont("times",10));
    info->setPlainText(QString("beam turret\n"
                               "dmg: 100%"));
    info->setDefaultTextColor(Qt::white);

    hide();
    info->hide();
}

QRectF InfoTurret::boundingRect() const
{
    return QRectF(-75,-75,150,150);
}

void InfoTurret::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawPixmap(-75,-75, *icon, 0, 0, 150,150);
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
