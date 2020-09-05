#ifndef ACCOUNTCREATION_H
#define ACCOUNTCREATION_H

#include <QDialog>
#include "user.h"


namespace Ui {
class AccountCreation;
}

class AccountCreation : public QDialog
{
    Q_OBJECT

public:
    explicit AccountCreation(QWidget *parent = nullptr);
    ~AccountCreation();
    User getUser();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AccountCreation *ui;
};

#endif // ACCOUNTCREATION_H
