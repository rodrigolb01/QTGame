#include <QApplication>
#include "game.h"
#include "mainwindow.h"


Game * game;
MainWindow* w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow();
    w->show();



    return a.exec();
}
