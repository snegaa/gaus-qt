#include "rezkfilter.h"

RezkFilter::RezkFilter()
{

}

void RezkFilter::createKernel(double **masKernel, int radius)
{
    double gaus[radius][radius] = {{1,-2,1},{-2,5,-2},{1,-2,1}};
    for (int i = 0; i < radius; ++i)
    {
        for (int j = 0; j < radius; ++j)
        {
            masKernel[i][j] = gaus[i][j];
        }
    }
    return;
}

QString RezkFilter::key()
{
    return "Rezkost";
}

QString RezkFilter::description()
{
    return "Усиление резкости";
}
