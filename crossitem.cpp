#include "crossitem.h"
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QColor>
#include <QRgb>
#include <math.h>
#include <QVector>

CrossItem::CrossItem(QGraphicsItem *parent)
{
    qDebug() << img.load("/tiger.bmp");

    //img.load("/2.jpeg");
    //img.load("./debug/2.bmp");
}

void CrossItem::createKernel(double **masKernel, int radius)
{
    //double masKernel[3][3];// значения радиуса(val) размытия, по ст.=3
    double sigma = 1.0;// стандартьное отклонение по стандарту=1
    double r, s = 2.0 * sigma * sigma;//радиус(r) и 2сигма в квадрате
    double div = 0.0; // сумма для нормализации

    int koff = radius / 2;

    for (int u = -1 * radius / 2; u <= radius / 2; u++)
        {
            for(int v = -1 * radius / 2; v <= radius / 2; v++)
            {
                r = (u*u + v*v);
                masKernel[u + koff][v + koff] = 1 /(M_PI * s)*exp(-r/s);
                div += masKernel[u + koff][v + koff];
            }
        }

    for (int i = 0; i < radius; ++i) //для нормализации чтобы не осветлялось или затемнялось изображение
    {
        for (int j = 0; j < radius; ++j)
        {
             masKernel[i][j] /= div;
        }
    }
}

void CrossItem::modern()
{       
    int radius = 3;
    int koffBorder = radius / 2 * 2;
    int halfKoff = koffBorder / 2;
    QVector< QVector<QColor> > start; // [img.width()+2][img.height()+2]; //массив пикселей?
    start.resize(img.width()+koffBorder);
    for (int i = 0; i < img.width()+koffBorder; ++i) start[i].resize(img.height()+koffBorder);
    start[0][0] = QColor(img.pixel(0, 0));
    start[img.width()+1][0] = QColor(img.pixel(img.width()-1, 0));
    start[0][img.height()+1] = QColor(img.pixel(0, img.height()-1));
    start[img.width()+1][img.height()+1] = QColor(img.pixel(img.width()-1, img.height()-1));


   // double** gaus = new double*[radius]; //[radius][radius] = {{1,1,1},{1,1,1},{1,1,1}};
   // for (int k = 0; k < radius; ++k) gaus[k] = new double[radius];
   // this->createKernel((double**)gaus, radius);

    for (int y = 0; y < img.height(); ++y)
    {
        start[0][y+1] = QColor(img.pixel(0, y));
        start[img.width()+1][y+1] = QColor(img.pixel(img.width()-1, y));
    }
    for (int x = 0; x < img.width(); ++x)
    {
        start[x+1][0] = QColor(img.pixel(x, 0));
        start[x+1][img.height()+1] = QColor(img.pixel(x, img.height()-1));
    }

    for (int x =0; x < img.width(); ++x)
    {
        for (int y = 0; y < img.height(); ++y)
        {
            start[x+1][y+1] = QColor(img.pixel(x, y));
        }
    }
//типо Гаусса
   // double gaus[radius][radius] = {{0.5,0.75,0.5},{0.75,1,0.75},{0.5,0.75,0.5}};
  //усиление резкости
    double gaus[radius][radius] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};

    for (int x = 1; x <= img.width(); ++x)
    {
        for (int y = 1; y <= img.height(); ++y)
        {
            double summ_pixel = 0;
            double summ_gaus = 0;
            int koff = -1 * radius / 2;
            for (int i = 0; i < radius; i++)
            {
                for (int j=0; j < radius; j++)
                {
                    summ_pixel += start[x+ koff +i][y+koff+j].value() * gaus[i][j];
                    summ_gaus += gaus[i][j];
                }
            }
            int result = ceil(summ_pixel / summ_gaus);
            if (result > 255) result = 255;
            QColor value = QColor(img.pixel(x-1, y-1));
            value.setHsv(value.hue(), value.saturation(), result, value.alpha());
            img.setPixel(x-1, y-1, value.rgb());
        }
    }

//    QColor color(img.pixel(x, y));// координаты пикселей от начала до конца изображения
//    int new_value = 1;

//    color.setHsv(color.hsvHue(), color.hsvSaturation(), (new_value) % 256, color.alpha());

}

QRectF CrossItem::boundingRect() const  //устанавливает координаты элемнта - это рамочка? aga
{
    return QRectF(0,0,img.width(),img.height()); //с (х.у) загружается картинка размерами 500 на 300
}

void CrossItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   // painter->drawRect(boundingRect());
    painter->drawImage(boundingRect().toRect(), img);
}

