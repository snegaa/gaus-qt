#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H
#include "basefilter.h"

class MedianFilter : public BaseFilter
{
public:
    MedianFilter();
    virtual void createKernel(double **masKernel, int radius);
    static QString key();
    static QString description();
};

#endif // MEDIANFILTER_H
