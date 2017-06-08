#include "relfilter.h"

RelFilter::RelFilter()
{

}
void RelFilter::createKernel(double **masKernel, int radius)
{
    double gaus[radius][radius] = {{-2,-1,0},{-1,1,1},{0,1,2}};
    for (int i = 0; i < radius; ++i)
    {
        for (int j = 0; j < radius; ++j)
        {
            masKernel[i][j] = gaus[i][j];
        }
    }
    return;
}

QString RelFilter::key()
{
    return "Relef";
}

QString RelFilter::description()
{
    return "Рельефность";
}
