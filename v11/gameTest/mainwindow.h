#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <QMessageBox>
#include <QSqlQuery>

#include "user.h"
/*
 * this class will create an login screen and authenticate the user login/password
 *  and so launch the game, or create an
 * 'accountcreation' window for register the user if it does not have an account yet
 */
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_login_clicked();//it will access the game database and validate the login and password
    void on_pushButton_newAccount_clicked();//will lead the user to registrate in the game database
private:
    Ui::MainWindow *ui;
    void addUser(User newUser);//insert the new user login and password into the database
    int flaglogin=0;
};

#endif // MAINWINDOW_H
