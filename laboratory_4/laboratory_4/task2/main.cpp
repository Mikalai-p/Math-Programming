#include <iostream>
#include <ctime>
#include <cstring>
#include <clocale>
#include "LSC.h"

int main()
{
    setlocale(LC_ALL, "rus");
    clock_t t1 = 0, t2 = 0, t3 = 0, t4 = 0;

    const char* X = "ABHCSUV";
    const char* Y = "KIBOSV";

    t1 = clock();
    int s = lcs(strlen(X), X, strlen(Y), Y);
    t2 = clock();

    char z[100] = "";
    t3 = clock();
    int l = lcsd(X, Y, z);
    t4 = clock();

    std::cout << std::endl << "вычисление длины LCS для X и Y (рекурсия)";
    std::cout << std::endl << "последовательность X: " << X;
    std::cout << std::endl << "последовательность Y: " << Y;
    std::cout << std::endl << "длина LCS: " << s << std::endl;

    std::cout << std::endl << "-- наибольшая общая подпоследовательность - LCS (динамическое программирование)" << std::endl;
    std::cout << std::endl << "последовательность X: " << X;
    std::cout << std::endl << "последовательность Y: " << Y;
    std::cout << std::endl << "                LCS: " << z;
    std::cout << std::endl << "          длина LCS: " << l;
    std::cout << std::endl;

    std::cout << '\n' << "Время выполнения рекурсивно: " << (t2 - t1);
    std::cout << '\n' << "Время выполнения динамически: " << (t4 - t3) << '\n' << std::endl;

    system("pause");
    return 0;
}