#include "accountcreation.h"
#include "ui_accountcreation.h"
#include "QMessageBox"

User newUser;

AccountCreation::AccountCreation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountCreation)
{
    ui->setupUi(this);
}

AccountCreation::~AccountCreation()
{
    delete ui;
}

User AccountCreation::getUser()
{
   return newUser;
}

void AccountCreation::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString confirmP = ui->lineEdit_passwordConfirm->text();

    if (password == confirmP)
    {
        QMessageBox::information(this,"User","registrarion successful!");
        newUser.setUsername(username);
        newUser.setPassword(password);

        getUser();
    }
    else
    {
        QMessageBox::warning(this,"User","passwords differ from each other");
    }
}

