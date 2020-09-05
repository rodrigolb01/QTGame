#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "accountcreation.h"
#include "user.h"
#include "game.h"

User users[9];
int index=0;
int flaglogin=0;//storage users

 extern Game* game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString login = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    for(int i=0; i< index; i++)
    {
        if(login == users[i].login && password == users[i].password)
        {
            flaglogin = 1;
        }
    }
    if(flaglogin==1)
    {
        ui->statusbar->showMessage("login successful",5000);
        flaglogin=0;

        hide();
        game = new Game();
        game->show();
    }
    else if(flaglogin==0)
    {
        ui->statusbar->showMessage("login/password invalid!",5000);

    }
}

void MainWindow::addUser(User newUser)
{
    users[index] = newUser;
    index++;
}

void MainWindow::on_pushButton_newAccount_clicked()
{
    AccountCreation a;
    a.setModal(true);
    a.exec();
    addUser(a.getUser());

}

User getUser(User user)
{
    return user;
}
