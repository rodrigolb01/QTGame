#ifndef HPBAR_H
#define HPBAR_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QRectF>
#include <QBrush>

class HPbar : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit HPbar(QObject *parent = nullptr);
    QGraphicsRectItem* bar;
    qreal lenght=80;

    void increase();
    void decrease();

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // HPBAR_H
