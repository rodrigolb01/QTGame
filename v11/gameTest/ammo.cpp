#include "ammo.h"
#include <QFont>

Ammo::Ammo(QGraphicsItem *parent)
{
    ammo=20;
    setPlainText(QString("Ammo: ") + QString::number(ammo));
    setFont(QFont("times",10));
    setDefaultTextColor(Qt::green);
    setPos(1010,160);
}

void Ammo::increase()
{
    ammo++;
    setPlainText(QString("Ammo: ") + QString::number(ammo));
}

void Ammo::decrease()
{
    ammo--;
    setPlainText(QString("Ammo: ") + QString::number(ammo));

}
