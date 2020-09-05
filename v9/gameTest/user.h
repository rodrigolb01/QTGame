#ifndef USER_H
#define USER_H

#include "QString"

class User
{
public:
    User();
    QString login;
    QString password;
    void setUsername(QString newLogin)
    {
        this->login = newLogin;
    }
    void setPassword(QString newPassword)
    {
        this->password = newPassword;
    }
    QString getLogin()
    {
        return this->login;
    }
    QString getPassword()
    {
        return this->password;
    }
};

#endif // USER_H
