#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include "score.h"
#include "health.h"
#include "player.h"
#include "ship.h"
#include "ammo.h"
#include "infoplayer.h"
#include "stationaryObject.h"
#include "display.h"


//class that contains all game objects and game logic.
class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent=0);
    Display *display;
    QGraphicsScene * scene;
    Player * player1;
    Ship * mothership1;

    InfoPlayer *playeri;
    StationaryObject *w;
    StationaryObject *x;

    QTimer* setfocusTimer;
    QTimer* setplayerHpTimer;

    void setFocus();//sets the current focus
    void setPlayerHpBar();
    void mousePressEvent(QMouseEvent *event) ;
};

#endif // GAME_H
