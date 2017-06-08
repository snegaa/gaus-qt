#ifndef REZKFILTER_H
#define REZKFILTER_H
#include "basefilter.h"

class RezkFilter : public BaseFilter
{
public:
    RezkFilter();
    virtual void createKernel(double **masKernel, int radius);
    static QString key();
    static QString description();

};

#endif // REZKFILTER_H
