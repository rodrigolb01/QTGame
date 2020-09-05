#ifndef ANGLEDBULLET_H
#define ANGLEDBULLET_H
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class angledBullet: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit angledBullet(QGraphicsItem *parent=0,int bulletShooter=0);

public slots:
    void move();
private slots:
    void nextFrame();
private:
    int bulletShooter;
    int currentFrame;
    int currentRow;
    int animationEnd;
    bool animationStarted;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QTimer *moveTimer;
    QTimer *animationTimer;
    QPixmap *bulletPic;
};

#endif // ANGLEDBULLET_H
