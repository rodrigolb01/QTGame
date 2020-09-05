#include "mainwindow.h"
#include "ui_mainwindow.h"



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

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "conn");
        db.setHostName("localhost");
        db.setDatabaseName("postgres");
        db.setUserName("postgres");
        db.setPassword("m4a10121");
        bool ok = db.open();

        if(!ok)
        {
            QMessageBox::warning(this, "connection", "Connection failed! Driver not loaded.");
        }
        else
        {
            QSqlQuery q(db);
            q.prepare("SELECT username, password FROM users ");
            if(q.exec())
            {
               while(q.next())
               {
                   if(q.value(0).toString() == login)
                   {
                       if(q.value(1).toString() == password)
                           flaglogin = 1;
                   }
               }
            }
            else
            {
                QMessageBox::warning(this, "querry", "querry failed!");
            }
        }
    if(flaglogin==1)//if successful, we'll create and launch a game for this user
    {
        ui->statusbar->showMessage("login successful",5000);
        flaglogin=0;
        GameWindow *gameWindow = new GameWindow;
        close();//close this window
        gameWindow->show();
    }
    else if(flaglogin==0)
    {
        ui->statusbar->showMessage("login/password invalid!",5000);

    }
}

void MainWindow::addUser(User newUser)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "conn");
        db.setHostName("localhost");
        db.setDatabaseName("postgres");
        db.setUserName("postgres");
        db.setPassword("m4a10121");
        bool ok = db.open();

        if(!ok)
        {
            QMessageBox::warning(this, "connection", "Connection failed! Driver not loaded.");
        }
        else
        {
            QMessageBox::information(this, "connection", "connection succesful!");

            QSqlQuery q(db);
            QString insert = QString ("INSERT INTO users (username, password) VALUES('%1', '%2');").arg(newUser.login, newUser.password);
            q.prepare(insert);
            if(q.exec())
            {
                QMessageBox::information(this, "querry", "querry succesful!"); //retrieve data
                db.commit();
                db.close();
            }
            else
            {
                QMessageBox::warning(this, "querry", "querry failed!");
                db.close();
            }
        }

}

void MainWindow::on_pushButton_newAccount_clicked()
{
    a = new AccountCreation;
    a->setModal(true);
    a->exec();
    addUser(a->getUser());

}

User getUser(User user)
{
    return user;
}
