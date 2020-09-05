#ifndef AMMO_H
#define AMMO_H

#include <QGraphicsTextItem>

//creates a counter for ammo in the game class
class Ammo : public QGraphicsTextItem
{
public:
    Ammo(QGraphicsItem *parent = 0);
    void increase();
    void decrease();
    int ammo;
};

#endif // AMMO_H
