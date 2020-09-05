#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "MyRect.h"
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene * scene = new QGraphicsScene();

    MyRect * player = new MyRect();
    player->setRect(0, 0, 100, 100);
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable); //focused item
    player->setFocus();


    QGraphicsView * view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
    view->setFixedSize(800,600);
    scene->setSceneRect(0,0,800,600);

    player->setPos(view->width()/2, view->height()-player->rect().height());

    //spawn enemies

    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(3000);

    return a.exec();
}
