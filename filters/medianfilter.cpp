#include "medianfilter.h"

MedianFilter::MedianFilter()
{

}

void MedianFilter::createKernel(double **masKernel, int radius)
{
    double gaus[radius][radius] = {{1,0,1},{0,0,0},{1,0,1}};
    for (int i = 0; i < radius; ++i)
    {
        for (int j = 0; j < radius; ++j)
        {
            masKernel[i][j] = gaus[i][j];
        }
    }
    return;
}

QString MedianFilter::key()
{
    return "median";
}

QString MedianFilter::description()
{
    return "Медианный фильтр";
}
