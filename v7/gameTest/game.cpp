#include "game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>


Game::Game(QWidget *parent)
{
    // create the scene
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,1200,800);

    setBackgroundBrush(QBrush(QImage(":/images/img/background2.png")));

    // make the new created scene the scene to visualize
    setScene(scene);

    setFixedSize(1200,800);

    // create the player
    player1 = new Sprite();

    player1->setPos((scene->width()/2) - player1->pos().x(), scene->height()/2);// TODO generalizes to be aways in the mid botton of the screen

    // make the player focusable
    player1->setFlag(QGraphicsItem::ItemIsFocusable);
    player1->setFocus();

    // add the player to the scene
    scene->addItem(player1);

    // create the score
    score = new Score();
    scene->addItem(score);

    // create the health
    health = new Health();
    scene->addItem(health);

    // spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player1,SLOT(spawn()));
    timer->start(2000);
    show();

}
