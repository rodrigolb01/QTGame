#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "game.h"
#include "mainwindow.h"

 extern Game* game;

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_pushButton_clicked()
{
    game = new Game(this);
    game->show();
    connect(game, &Game::Exit, this, &GameWindow::exitGame);

}

void GameWindow::exitGame(int gameover)
{
    if(gameover==1)
     {
        game->disconnect();
        delete game;
        qInfo() << "game deleted, gameover = " ,gameover;
     }
}


void GameWindow::on_pushButton_3_clicked()
{
    close();
    MainWindow* m = new MainWindow;
    m->show();
}
