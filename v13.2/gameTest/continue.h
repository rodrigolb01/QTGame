#ifndef CONTINUE_H
#define CONTINUE_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include <QTimer>

class Continue : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit Continue(QObject *parent = nullptr);
    int count=10;
    QMediaPlayer* gameOver;
    QTimer* t;
public slots:
    void decrease();
signals:
    void GameOver(int gameover);

};

#endif // CONTINUE_H
