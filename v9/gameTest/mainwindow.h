#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    User getUser(User user);
private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_newAccount_clicked();

    void addUser(User newUser);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
