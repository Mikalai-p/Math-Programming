#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int N = 5;
const int INF = 1e9;

// Матрица расстояний для n = 9
int dist[N][N] = {
    {INF, 9, 28, 12, 13},
    {10, INF, 21, 31, 59},
    {16, 18, INF, 72, 46},
    {27, 46, 27, INF, 18},
    {76, 41, 45, 21, INF}
};

int main() {
    setlocale(LC_ALL, "rus");
    vector<int> cities = { 2, 3, 4, 5 };  // города, которые нужно переставить
    int minCost = INF;
    vector<vector<int>> bestRoutes;

    // Фиксируем первый город = 1
    do {
        // Строим полный маршрут: 1 -> перестановка -> 1
        vector<int> route = { 1 };
        route.insert(route.end(), cities.begin(), cities.end());
        route.push_back(1);  // возврат в начало

        // Вычисляем стоимость
        int cost = 0;
        bool valid = true;
        for (size_t i = 0; i < route.size() - 1; ++i) {
            int from = route[i] - 1;  // индексация с 0
            int to = route[i + 1] - 1;
            if (dist[from][to] >= INF) {
                valid = false;
                break;
            }
            cost += dist[from][to];
        }

        if (valid && cost < minCost) {
            minCost = cost;
            bestRoutes.clear();
            bestRoutes.push_back(route);
        }
        else if (valid && cost == minCost) {
            bestRoutes.push_back(route);
        }
    } while (next_permutation(cities.begin(), cities.end()));

    // Вывод результатов
    cout << "Минимальная стоимость: " << minCost << endl;
    cout << "Оптимальные маршруты (начало и конец в городе 1):" << endl;
    for (const auto& route : bestRoutes) {
        for (size_t i = 0; i < route.size(); ++i) {
            cout << route[i];
            if (i != route.size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    return 0;
}