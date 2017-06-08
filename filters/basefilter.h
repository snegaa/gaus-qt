#ifndef BASEFILTER_H
#define BASEFILTER_H
#include <QString>

class BaseFilter
{
public:
    BaseFilter();

    virtual void createKernel(double **masKernel, int radius) = 0;
    static QString key();
    static QString description();
};

#endif // BASEFILTER_H
