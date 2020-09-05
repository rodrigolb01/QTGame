#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include "game.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void on_pushButton_clicked();
    void exitGame(int gameover);

    void on_pushButton_3_clicked();

private:
    Ui::GameWindow *ui;

};

#endif // GAMEWINDOW_H
