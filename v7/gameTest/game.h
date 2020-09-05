#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "score.h"
#include "health.h"
#include "sprite.h"

//object that contains all objects and game logic
class Game: public QGraphicsView
{
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    Sprite * player1;
    Score * score;
    Health * health;
};

#endif // GAME_H
