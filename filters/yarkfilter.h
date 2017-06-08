#ifndef YARKFILTER_H
#define YARKFILTER_H
#include "basefilter.h"

class YarkFilter : public BaseFilter
{
public:
    YarkFilter();
    virtual void createKernel(double **masKernel, int radius);
    static QString key();
    static QString description();
};

#endif // YARKFILTER_H
