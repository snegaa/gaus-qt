#include <QCoreApplication>
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

void createFilter(double gKernel[0][3])
{
    // set standard deviation to 1.0
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    // sum is for normalization
    double sum = 0.0;

    // generate 3x3 kernel
    for (int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {

           // gKernel[x + 1][y + 1] = exp(-((x*x) + (y*y))/s)/(M_PI * s);
            gKernel[x + 1][y + 1] = 1 / (M_PI * s)*exp(-((x*x)+(y*y)/s));
            sum += gKernel[x + 1][y + 1];
        }
    }

    // normalize the Kernel
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            gKernel[i][j] /= sum;

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    double gKernel[3][3];
        createFilter(gKernel);
        for(int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
                cout<<gKernel[i][j]<<"\t";
            cout<<endl;
        }

    return 0;
}
