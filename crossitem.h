#ifndef CROSSITEM_H
#define CROSSITEM_H

#include <QGraphicsItem>
#include <QImage>
#include <QPixmap>
#include "filters/basefilter.h"
#include <QString>

class CrossItem : public QGraphicsItem
{
    QImage img;
    //QPixmap myPixmap;
    double state;
    QString mFileName;
    void setState(int i, int j, int width, int height, int part);
public:
     explicit CrossItem(QString aFileName, QGraphicsItem *parent = Q_NULLPTR);

     ~CrossItem(){}

     virtual QRectF boundingRect() const;
     virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void modern(BaseFilter* filter);

    QImage getImage();
    double getState();
    void reload();

};

#endif // CROSSITEM_H
