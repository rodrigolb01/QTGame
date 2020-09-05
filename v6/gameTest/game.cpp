#include "game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "enemy.h"
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>

Game::Game(QWidget *parent)
{
    // create the scene
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,800,600);

    setBackgroundBrush(QBrush(QImage(":/images/img/background1.png")));

    // make the new created scene the scene to visualize
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // create the player
    player = new MyRect();

    player->setPos(scene->width()/2,scene->height()/2);// TODO generalizes to be aways in the mid botton of the screen

    // make the player focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add the player to the scene
    scene->addItem(player);

    // create the score
    score = new Score();
    scene->addItem(score);

    // create the health
    health = new Health();
    scene->addItem(health);

    // spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(3000);

    show();

}
