#ifndef GAUSFILTER_H
#define GAUSFILTER_H
#include "basefilter.h"

class GausFilter : public BaseFilter
{
public:
    GausFilter();
    virtual void createKernel(double **masKernel, int radius);
    static QString key();
    static QString description();
};

#endif // GAUSFILTER_H
