#include "yarkfilter.h"

YarkFilter::YarkFilter()
{

}
void YarkFilter::createKernel(double **masKernel, int radius)
{
    double gaus[radius][radius] = {{0,0,0},{2,20,200},{0,0,0}};
    for (int i = 0; i < radius; ++i)
    {
        for (int j = 0; j < radius; ++j)
        {
            masKernel[i][j] = gaus[i][j];
        }
    }
    return;
}

QString YarkFilter::key()
{
    return "Yarkost";
}

QString YarkFilter::description()
{
    return "Повышение цветового контраста";
}
