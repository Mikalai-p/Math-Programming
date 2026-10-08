#include "pch.h"
#include "Auxil.h"
#define  CYCLE 1000000                

using namespace std;

int main()
{

	double  av1 = 0, av2 = 0;
	clock_t  t1 = 0, t2 = 0, t3 = 0, t4 = 0;

	setlocale(LC_ALL, "rus");

	auxil::start();                          
	t1 = clock();                            
	for (int i = 0; i < CYCLE; i++)
	{
		av1 += static_cast<double>(auxil::iget(-100, 100));  
		av2 += auxil::dget(-100, 100);         
	}
	t2 = clock();                            


	std::cout << std::endl << "количество циклов:         " << CYCLE;
	std::cout << std::endl << "среднее значение (int):    " << av1 / CYCLE;
	std::cout << std::endl << "среднее значение (double): " << av2 / CYCLE;
	std::cout << std::endl << "продолжительность (у.е):   " << (t2 - t1);
	std::cout << std::endl << "                  (сек):   "
		<< static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
	std::cout << std::endl;
	return 0;
}
