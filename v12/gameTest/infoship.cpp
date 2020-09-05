#include "infoship.h"
#include <QBrush>
#include <QPainter>
#include <QFont>

InfoShip::InfoShip(QObject *parent) : QObject(parent)
{
    icon = new QPixmap(":/images/img/battleshipInfo1.png");

    info = new QGraphicsTextItem();
    info->setPos(pos());
    info->setFont(QFont("times",10));
    info->setPlainText(QString("Nagel Argama\n"
                               "HP: 100%"));
    info->setDefaultTextColor(Qt::white);

    hide();
    info->hide();
}

QRectF InfoShip::boundingRect() const
{
     return QRectF(-75,-75,150,150);
}

void InfoShip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawPixmap(-75,-75, *icon, 0, 0, 150,150);
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
