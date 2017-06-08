#ifndef KONTURFILTER_H
#define KONTURFILTER_H
#include "basefilter.h"

class KonturFilter : public BaseFilter
{
public:
    KonturFilter();
    virtual void createKernel(double **masKernel, int radius);
    static QString key();
    static QString description();
};

#endif // KONTURFILTER_H
