#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>
#include <QKeyEvent>


class MyRect :public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    MyRect(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
private:
    QMediaPlayer * bullet_sound;

public slots:
void spawn();
};


#endif // MYRECT_H
