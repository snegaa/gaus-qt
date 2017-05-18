#ifndef CROSSITEM_H
#define CROSSITEM_H

#include <QGraphicsItem>
#include <QImage>
#include <QPixmap>

class CrossItem : public QGraphicsItem
{
    QImage img;
    //QPixmap myPixmap;
public:
     explicit CrossItem(QGraphicsItem *parent = Q_NULLPTR);

     ~CrossItem(){}

     virtual QRectF boundingRect() const;
     virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void modern();
    void createKernel(double **masKernel, int radius);
};

#endif // CROSSITEM_H
