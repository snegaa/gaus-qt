#include "konturfilter.h"

KonturFilter::KonturFilter()
{

}

void KonturFilter::createKernel(double **masKernel, int radius)
{
    double gaus[radius][radius] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};
    for (int i = 0; i < radius; ++i)
    {
        for (int j = 0; j < radius; ++j)
        {
            masKernel[i][j] = gaus[i][j];
        }
    }
    return;



}

QString KonturFilter::key()
{
    return "kontur";
}

QString KonturFilter::description()
{
    return "Контурный фильтр";
}
