#include "stdafx.h"
#include <cmath>
#include <memory.h>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Levenstein.h"
using namespace std;

#define FIRST_LEN 300
#define SECOND_LEN 200

char* Task1(int size)
{
    char* str = new char[size + 1];
    for (int i = 0; i < size; i++)
        str[i] = rand() % 26 + 'a';
    str[size] = '\0';
    return str;
}

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "rus");
    srand((unsigned int)time(nullptr));

    // Генерация строк
    char* s1 = Task1(FIRST_LEN);
    cout << "S1 (300 символов):" << endl;
    for (int i = 0; i < FIRST_LEN; i++)
    {
        if (i % 50 == 0 && i != 0) cout << "\n";
        cout << s1[i];
    }
    cout << endl << endl;

    srand((unsigned int)time(nullptr) + 1);
    char* s2 = Task1(SECOND_LEN);
    cout << "S2 (200 символов):" << endl;
    for (int i = 0; i < SECOND_LEN; i++)
    {
        if (i % 50 == 0 && i != 0) cout << "\n";
        cout << s2[i];
    }
    cout << endl << endl;

    // Пары длин
    int s1_sizes[] = { FIRST_LEN / 25, FIRST_LEN / 20, FIRST_LEN / 15,
                       FIRST_LEN / 10, FIRST_LEN / 5, FIRST_LEN / 2, FIRST_LEN };
    int s2_sizes[] = { SECOND_LEN / 25, SECOND_LEN / 20, SECOND_LEN / 15,
                       SECOND_LEN / 10, SECOND_LEN / 5, SECOND_LEN / 2, SECOND_LEN };
    int num_tests = sizeof(s1_sizes) / sizeof(s1_sizes[0]);

    // 1. ДИНАМИЧЕСКОЕ ПРОГРАММИРОВАНИЕ 
    cout << "\n\nДИНАМИЧЕСКОЕ ПРОГРАММИРОВАНИЕ\n";
    cout << "длина(S1/S2)    время \n";
    for (int i = 0; i < num_tests; i++)
    {
        int len1 = s1_sizes[i];
        int len2 = s2_sizes[i];

        clock_t t3 = clock();
        int d = levenshtein(len1, s1, len2, s2);
        clock_t t4 = clock();
        long long dyn_time = (t4 - t3);

        cout << right << setw(2) << len1 << "/" << setw(2) << len2
            << "        " << left << setw(10) << dyn_time << endl;
    }

    // 2. РЕКУРСИВНОЕ ПРОГРАММИРОВАНИЕ 
    cout << "\n\nРЕКУРСИВНОЕ ПРОГРАММИРОВАНИЕ\n";
    cout << "длина(S1/S2)    время (тики)    примечание\n";
    for (int i = 0; i < num_tests; i++)
    {
        int len1 = s1_sizes[i];
        int len2 = s2_sizes[i];

        if (len1 <= 25 && len2 <= 25)
        {
            clock_t t1 = clock();
            int r = levenshtein_r(len1, s1, len2, s2);
            clock_t t2 = clock();
            long long rec_time = (t2 - t1);
            cout << right << setw(2) << len1 << "/" << setw(2) << len2
                << "        " << left << setw(10) << rec_time
                << "    выполнено" << endl;
        }
        else
        {
            cout << right << setw(2) << len1 << "/" << setw(2) << len2
                << "        " << left << setw(10) << "---"
                << "    слишком долго" << endl;
        }
    }

    delete[] s1;
    delete[] s2;
    system("pause");
    return 0;
}