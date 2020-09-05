#include "game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <background.h>
#include "eff_explosion.h"

Game::Game(QWidget *parent)
{
    // create the scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1200,800);

    background = new QPixmap(":/images/img/background4.png");

    // make the new created scene the scene to visualize
    setScene(scene);

    setFixedSize(1200,800);

    Background* b = new Background();
    b->setPos(600,400);
    scene->addItem(b);

    //create mothership
    mothership1 = new Ship(this);
    mothership1->setPos(500,300);
    mothership1->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(mothership1);
    //create turret
    mothership1->t->setPos(612,435);
    mothership1->t->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(mothership1->t);
    //turret info
    mothership1->t->turretInfo = new InfoTurret(mothership1);
    mothership1->t->turretInfo->setPos(1082,60);
    mothership1->t->turretInfo->setZValue(10);
    //
    scene->addItem(mothership1->t->turretInfo->info);
    mothership1->t->turretInfo->info->setPos(1050,130);
    mothership1->t->turretInfo->info->setZValue(10);
    //
    mothership1->t->turretInfo->hpBar = new HPbar(mothership1);
    mothership1->t->turretInfo->hpBar->bar->setPos(mothership1->t->x()+10, mothership1->t->y()-40);
    mothership1->t->turretInfo->hpBar->bar->setZValue(10);
    scene->addItem(mothership1->t->turretInfo->hpBar);
    scene->addItem(mothership1->t->turretInfo->hpBar->bar);

    //ship info
    mothership1->battleshipInfo = new InfoShip(mothership1);
    mothership1->battleshipInfo->setPos(1080,80);
    mothership1->battleshipInfo->setZValue(10);
    //
    scene->addItem(mothership1->battleshipInfo->info);
    mothership1->battleshipInfo->info->setPos(1050,130);
    mothership1->battleshipInfo->info->setZValue(11);

    scene->addItem(mothership1->battleshipInfo);
    scene->addItem(mothership1->t->turretInfo);
    scene->addItem(mothership1->t->turretInfo->hpBar);


    // create the playable character
    player1 = new Player(this);
    player1->setPos((scene->width()/2) - player1->pos().x() + 20, scene->height()/2 - 200);// TODO generalizes to be aways in the mid botton of the screen
    //
    player1->info = new InfoPlayer(player1);
    scene->addItem(player1->info);
    scene->addItem(player1->info->health);
    scene->addItem(player1->info->score);
    scene->addItem(player1->info->ammo);
    scene->addItem(player1->info->hpBar);
    scene->addItem(player1->info->hpBar->bar);
    player1->info->health->setZValue(10);
    player1->info->score->setZValue(10);
    player1->info->ammo->setZValue(10);
    player1->info->setZValue(9);
    player1->info->setPos(1080,85);
    // make the character focusable
    player1->setFlag(QGraphicsItem::ItemIsFocusable);
    player1->setFocus();
    scene->addItem(player1);

    //set focus timer
    setfocusTimer = new QTimer;
    connect(setfocusTimer, &QTimer::timeout, this, &Game::setFocus);
    setfocusTimer->start(50);

    setplayerHpTimer = new QTimer;
    connect(setplayerHpTimer, &QTimer::timeout, this, &Game::setPlayerHpBar);
    setplayerHpTimer->start(20);

    display = new Display;
    display->setPos(1085,120);
    display->setZValue(8);
    scene->addItem(display);
    show();

}


void Game::setFocus()
{
    if(scene->focusItem() == NULL)//set the player to be the default focus item
        player1->setFocus();

    if(scene->focusItem() == player1)
    {
        player1->info->show();
        player1->info->health->show();
        player1->info->score->show();
        player1->info->ammo->show();
        player1->info->hpBar->bar->show();
    }
    else
    {
        player1->info->hide();
        player1->info->health->hide();
        player1->info->score->hide();
        player1->info->ammo->hide();
        player1->info->hpBar->bar->hide();
    }

    if(scene->focusItem() == mothership1)
    {
        mothership1->battleshipInfo->show();
        mothership1->battleshipInfo->info->show();
    }
    else
    {
        mothership1->battleshipInfo->hide();
        mothership1->battleshipInfo->info->hide();
    }

    if(scene->focusItem() == mothership1->t)
    {
        mothership1->t->turretInfo->show();
        mothership1->t->turretInfo->info->show();
        mothership1->t->attack_area->show();
        mothership1->t->turretInfo->hpBar->bar->show();
    }
    else
    {
        mothership1->t->turretInfo->hide();
        mothership1->t->turretInfo->info->hide();
        mothership1->t->attack_area->hide();
        mothership1->t->turretInfo->hpBar->bar->hide();
    }
}

void Game::setPlayerHpBar()
{
    player1->info->hpBar->bar->setPos(player1->x(),player1->y()-50);
    if(player1->info->hpBar->lenght <= 0)
    {
        EFF_Explosion* f = new EFF_Explosion;
        f->setPos(player1->pos());
        scene->addItem(f);

        player1->hide();//if hp bar is zero, them player is dead.
        player1->setPos(9999,999);
        mothership1->setFocus();
        setplayerHpTimer->stop();
        Continue* c = new Continue(this);
        c->setPos(450,350);
        connect(c,&Continue::GameOver, this, &Game::shutdown);
        scene->addItem(c);
    }
}

void Game::shutdown(int gameover)
{
    if(gameover==1)//end this game
    {
        shutdownt = new QTimer;
        connect(shutdownt, &QTimer::timeout, this, &Game::close);
        shutdownt->start(2000);
    }
}

void Game::close()
{
    disconnect(shutdownt, &QTimer::timeout, this, &Game::close);
    emit Exit(1);
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if(player1->boundingRect().contains(event->pos()))
    {
        player1->setFocus();
    }
    else if(mothership1->boundingPolygon->contains(event->pos()))
    {
        mothership1->setFocus();
    }
    else if(mothership1->t->boundingRect().contains(event->pos()))
    {
        mothership1->t->setFocus();
    }
    qDebug() << scene->focusItem();
}
