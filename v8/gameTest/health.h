#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

//creates a counter for health in the game class
class Health: public QGraphicsTextItem
{
public:
    Health(QGraphicsItem * parent=0);
    void decrease();
    void increase();
    int getHealth();
    int health;
};

#endif // HEALTH_H
