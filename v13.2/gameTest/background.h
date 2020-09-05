#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class Background : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Background(QObject *parent = nullptr);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPixmap* pic;
    int currentframe;
    QTimer* animtimer;
private slots:
    void nextFrame();

};

#endif // BACKGROUND_H
