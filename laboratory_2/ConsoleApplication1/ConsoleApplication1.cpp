#include <iostream>
#include <Windows.h>
#include <ctime>
#include "Combi.h"
#include "tcp.h"              
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char mas[][2] = { "A", "B", "C", "D", "E" };
    cout << "Генерация всех подмножеств множества:\n";
    cout << "Исходное множество:\n{";
    for (int i = 0; i < 5; i++) {
        cout << mas[i] << (i < 4 ? ", " : "");
    }
    cout << '}';
    cout << "\nВсе подмножества:\n";
    combi::subset s1(5);
    int n1 = s1.getfirst();

    while (n1 >= 0) {
        cout << '{';
        for (int i = 0; i < n1; i++) {
            cout << mas[s1.ntx(i)] << (i < n1 - 1 ? ", " : "");
        }
        cout << "}\n";
        n1 = s1.getnext();
    }
    cout << "Всего: " << s1.count() << "\n\n";

    cout << "Генерация сочетаний:\n";
    cout << "Исходное множество:\n{";
    for (int i = 0; i < 5; i++) {
        cout << mas[i] << (i < 4 ? ", " : "");
    }
    cout << '}';
    combi::xcombination s2(5, 2);
    int n2 = s2.getfirst();
    cout << "Все сочетания по " << s2.n << " из " << s2.m << '\n';

    while (n2 >= 0) {
        cout << s2.nc << " : { ";
        for (int i = 0; i < n2; i++) {
            cout << mas[s2.ntx(i)] << (i < n2 - 1 ? ", " : "");
        }
        cout << "}\n";
        n2 = s2.getnext();
    }
    cout << "Всего: " << s2.count() << "\n\n";

    cout << "Генерация перестановок:\n";
    cout << "Исходное множество:\n{";
    for (int i = 0; i < 5; i++) {
        cout << mas[i] << (i < 4 ? ", " : "");
    }
    cout << '}';
    combi::permutation s3(5);
    long long n3 = s3.getfirst();
    cout << "\nВсе перестановки:\n";

    while (n3 >= 0) {
        cout << s3.np << " : { ";
        for (int i = 0; i < s3.n; i++) {
            cout << mas[s3.ntx(i)] << (i < s3.n - 1 ? ", " : "");
        }
        cout << "}\n";
        n3 = s3.getnext();
    }
    cout << "Всего: " << s3.count() << "\n\n";

    cout << "Генерация размещений\n";
    cout << "Исходное множество:\n{";
    for (int i = 0; i < 5; i++) {
        cout << mas[i] << (i < 4 ? ", " : "");
    }
    cout << '}';
    combi::accomodation s4(5, 2);
    long long n4 = s4.getfirst();
    cout << "\nВсе размещения по " << s4.n << " из " << s4.m << '\n';

    while (n4 >= 0) {
        cout << s4.na << " : { ";
        for (int i = 0; i < 2; i++) {
            cout << mas[s4.ntx(i)] << (i < s4.m - 1 ? ", " : "");
        }
        cout << "}\n";
        n4 = s4.getnext();
    }
    cout << "Всего: " << s4.count() << "\n\n";

    // ========== ЗАДАЧА КОММИВОЯЖЕРА ==========
    const int nCities = 10;
    cout << "--- Задача коммивояжера ---\n";
    cout << "Количество городов: " << nCities << "\n";

    // Генерация матрицы расстояний
    srand(123); // фиксированный seed для воспроизводимости
    vector<vector<int>> dist(nCities, vector<int>(nCities, 0));
    for (int i = 0; i < nCities; ++i) {
        for (int j = i + 1; j < nCities; ++j) {
            int d = 10 + rand() % 291; 
            dist[i][j] = d;
            dist[j][i] = d;
        }
    }
    // Три бесконечных расстояния
    dist[0][1] = dist[1][0] = tspfuncs::INF;
    dist[2][3] = dist[3][2] = tspfuncs::INF;
    dist[4][5] = dist[5][4] = tspfuncs::INF;

    cout << "\nМатрица расстояний (INF = " << tspfuncs::INF << "):\n";
    for (int i = 0; i < nCities; ++i) {
        for (int j = 0; j < nCities; ++j) {
            if (dist[i][j] >= tspfuncs::INF) cout << "INF\t";
            else cout << dist[i][j] << "\t";
        }
        cout << "\n";
    }

    vector<int> bestRoute;
    int minDist = tspfuncs::tsp(nCities, dist, bestRoute);

    cout << "\nМинимальная длина пути: " << minDist << " км\n";
    cout << "Маршрут (города по порядку): ";
    for (int city : bestRoute) {
        cout << city << " ";
    }
    cout << "\n\n";

    // Замер времени для разного числа городов
    cout << "-- Замер времени на разных количествах городов --\n";
    cout << "Городов\tВремя (мс)\n";
    for (int n = 5; n <= 10; ++n) {
        // Формируем подматрицу для n городов (используем уже сгенерированные расстояния)
        vector<vector<int>> d(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                d[i][j] = d[j][i] = dist[i][j];
            }
        }

        clock_t t1 = clock();
        vector<int> route;
        int res = tspfuncs::tsp(n, d, route);
        clock_t t2 = clock();

        cout << n << "\t" << (t2 - t1) << "\n";
    }

    return 0;
}