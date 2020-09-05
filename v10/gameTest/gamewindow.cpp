#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "game.h"

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
    game = new Game;
    game->show();
}
