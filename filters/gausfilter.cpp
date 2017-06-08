#include "gausfilter.h"
#include <math.h>

GausFilter::GausFilter()
{

}

void GausFilter::createKernel(double **masKernel, int radius)
{
    double gaus[radius][radius] = {{0.5,0.75,0.5},{0.75,1,0.75},{0.5,0.75,0.5}}; // Гаусс
    for (int i = 0; i < radius; ++i)
    {
        for (int j = 0; j < radius; ++j)
        {
            masKernel[i][j] = gaus[i][j];
        }
    }
    return;


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

QString GausFilter::key()
{
    return "gaus";
}

QString GausFilter::description()
{
    return "фильтр Гаусса";
}
