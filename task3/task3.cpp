#include "Auxil.h"                           
#include <iostream>
#include <ctime>
#include <locale>
#include <tchar.h>

#define  CYCLE  1000000    


long long int Fib(long long int n) {
	if (n == 0) {
		return 0;
	}
	if (n == 1 || n == 2) {
		return 1;
	}
	return Fib(n - 1) + Fib(n - 2);
}

int _tmain(int argc, _TCHAR* argv[])
{

	double  av1 = 0, av2 = 0;
	clock_t  t1 = 0, t2 = 0;

	setlocale(LC_ALL, "rus");

	auxil::start();
	t1 = clock();
	for (int i = 0; i < CYCLE; i++)
	{
		av1 += (double)auxil::iget(-100, 100);
		av2 += auxil::dget(-100, 100);
	}
	t2 = clock();


	std::cout << std::endl << "количество циклов:         " << CYCLE;
	std::cout << std::endl << "среднее значение (int):    " << av1 / CYCLE;
	std::cout << std::endl << "среднее значение (double): " << av2 / CYCLE;
	std::cout << std::endl << "продолжительность (у.е):   " << (t2 - t1);
	std::cout << std::endl << "                  (сек):   "
		<< ((double)(t2 - t1)) / ((double)CLOCKS_PER_SEC);
	std::cout << std::endl;

	long long int n;
	for (int i = 32; i <= 40; i += 2) {
		std::cout << "n = " << i << '\n';
		t1 = clock();
		n = Fib(i);
		std::cout << "Fib(n) = " << n << '\n';
		t2 = clock();
		std::cout << "продолжительность (у.е):   " << (t2 - t1) << '\n';
	}
	system("pause");
	return 0;
}
