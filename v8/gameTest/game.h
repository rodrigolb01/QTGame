#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "score.h"
#include "health.h"
#include "player.h"
#include "ship.h"
#include <QObject>

//object that contains all objects and game logic
class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    Player * player1;
    Ship * mothership1;
    Score * score;
    Health * health;
};

#endif // GAME_H
