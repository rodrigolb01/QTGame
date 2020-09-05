#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

//creates a counter for score in the game class
class Score: public QGraphicsTextItem
{
public:
    Score(QGraphicsItem * parent=0);
    void increase();
    int getScore();
    int score;
};


#endif // SCORE_H
