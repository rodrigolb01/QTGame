#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QGraphicsPathItem>

class Display : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Display(QObject *parent = nullptr);
    QPixmap *pic;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};

#endif // DISPLAY_H
