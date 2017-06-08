#ifndef RELFILTER_H
#define RELFILTER_H
#include "basefilter.h"

class RelFilter : public BaseFilter
{
public:
    RelFilter();
    virtual void createKernel(double **masKernel, int radius);
    static QString key();
    static QString description();

};

#endif // RELFILTER_H
