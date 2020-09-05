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

    //create mothership
    mothership1 = new Ship();
    mothership1->setPos(500,300);
    scene->addItem(mothership1);
    //create turret
    mothership1->t = new Turret();
    mothership1->t->setPos(612,435);
    scene->addItem(mothership1->t);

    // create the playable character
    player1 = new Player();
    player1->setPos((scene->width()/2) - player1->pos().x(), scene->height()/2 + 100);// TODO generalizes to be aways in the mid botton of the screen

    // make the character focusable
    player1->setFlag(QGraphicsItem::ItemIsFocusable);
    player1->setFocus();

    // add the it to the scene
    scene->addItem(player1);

    // create the score counter
    score = new Score();
    scene->addItem(score);

    // create the health counter
    health = new Health();
    scene->addItem(health);

    show();

}
