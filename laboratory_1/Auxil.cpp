#include "Auxil.h" 
#include <ctime>    
namespace auxil
{
    void start()                          
    {
        srand(static_cast<unsigned int>(time(nullptr)));
    };
    double dget(double rmin, double rmax) 
    {
        return (static_cast<double>(rand())/RAND_MAX)*(rmax-rmin)+rmin;
    };
    int iget(int rmin, int rmax)         

    {
        return static_cast<int>(dget(static_cast<double>(rmin), static_cast<double>(rmax)));
    };
}
