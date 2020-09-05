#include "continue.h"
#include <QFont>

Continue::Continue(QObject *parent)
{
    setPlainText(QString("   CONTINUE?\n") + QString("         ") + (QString::number(count)));
    setFont(QFont("times",40));
    setDefaultTextColor(Qt::white);
    setPos(600,400);
    t = new QTimer(this);

    connect(t, &QTimer::timeout, this, &Continue::decrease);
    t->start(1000);

    gameOver = new QMediaPlayer;
    gameOver->setMedia(QUrl("qrc:/sounds/sounds/go.wav"));
    gameOver->setVolume(10);
}

void Continue::decrease()
{
    if(count>0)
    {
        count--;
        setPlainText(QString("   CONTINUE?\n") + QString("         ") + (QString::number(count)));
    }
    if(count==0)
    {
        setPlainText(QString("MISSION FAILED!"));
        if(gameOver->state() == QMediaPlayer::PlayingState)
        {
            gameOver->setPosition(0);
        }
        if(gameOver->state() == QMediaPlayer::StoppedState)
        {
            gameOver->play();
        }
        emit GameOver(1);

    }
}
