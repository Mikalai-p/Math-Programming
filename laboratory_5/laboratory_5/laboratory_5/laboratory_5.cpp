#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <queue>
#include <cmath>
#include <string>

using namespace std;

const int SUPPLIERS = 5;          // поставщики
const int CONSUMERS = 6;          // потребители
const int N = 9;                  // вариант

const int M_BAL = SUPPLIERS + 1;  // 6 поставщиков
const int N_BAL = CONSUMERS;      // 6 потребителей

void printMatrix(const vector<vector<int>>& cost, const vector<int>& supply, const vector<int>& demand) {
    cout << "\nМатрица стоимостей (" << M_BAL << "x" << N_BAL << "):\n";
    for (int i = 0; i < M_BAL; ++i) {
        for (int j = 0; j < N_BAL; ++j) {
            cout << setw(4) << cost[i][j] << " ";
        }
        if (i < SUPPLIERS)
            cout << " | запас: " << supply[i];
        else
            cout << " | фиктивный запас: " << supply[i];
        cout << "\n";
    }
    cout << "Потребности: ";
    for (int j = 0; j < N_BAL; ++j)
        cout << demand[j] << " ";
    cout << "\n\n";
}

struct Cell {
    int i, j;
    int alloc;
    Cell(int i_, int j_, int alloc_) : i(i_), j(j_), alloc(alloc_) {}
};

// Метод Фогеля для построения начального опорного плана
vector<vector<int>> vogelInitial(const vector<vector<int>>& cost,
    vector<int> supply,
    vector<int> demand) {
    int m = M_BAL, n = N_BAL;
    vector<vector<int>> alloc(m, vector<int>(n, 0));
    vector<bool> rowActive(m, true), colActive(n, true);
    int activeRows = m, activeCols = n;


    while (activeRows > 0 && activeCols > 0) {
        vector<int> rowPenalty(m, -1);
        for (int i = 0; i < m; ++i) {
            if (!rowActive[i] || supply[i] == 0) continue;
            int firstMin = numeric_limits<int>::max();
            int secondMin = numeric_limits<int>::max();
            for (int j = 0; j < n; ++j) {
                if (!colActive[j] || demand[j] == 0) continue;
                int c = cost[i][j];
                if (c < firstMin) {
                    secondMin = firstMin;
                    firstMin = c;
                }
                else if (c < secondMin) {
                    secondMin = c;
                }
            }
            if (secondMin == numeric_limits<int>::max())
                rowPenalty[i] = firstMin;  // только один доступный столбец
            else
                rowPenalty[i] = secondMin - firstMin;
        }

        vector<int> colPenalty(n, -1);
        for (int j = 0; j < n; ++j) {
            if (!colActive[j] || demand[j] == 0) continue;
            int firstMin = numeric_limits<int>::max();
            int secondMin = numeric_limits<int>::max();
            for (int i = 0; i < m; ++i) {
                if (!rowActive[i] || supply[i] == 0) continue;
                int c = cost[i][j];
                if (c < firstMin) {
                    secondMin = firstMin;
                    firstMin = c;
                }
                else if (c < secondMin) {
                    secondMin = c;
                }
            }
            if (secondMin == numeric_limits<int>::max())
                colPenalty[j] = firstMin;
            else
                colPenalty[j] = secondMin - firstMin;
        }

        int maxPenalty = -1;
        bool rowChosen = true;
        int idx = -1;
        for (int i = 0; i < m; ++i) {
            if (rowActive[i] && rowPenalty[i] > maxPenalty) {
                maxPenalty = rowPenalty[i];
                rowChosen = true;
                idx = i;
            }
        }
        for (int j = 0; j < n; ++j) {
            if (colActive[j] && colPenalty[j] > maxPenalty) {
                maxPenalty = colPenalty[j];
                rowChosen = false;
                idx = j;
            }
        }

        int best_i = -1, best_j = -1;
        if (rowChosen) {
            int i = idx;
            int minCost = numeric_limits<int>::max();
            for (int j = 0; j < n; ++j) {
                if (colActive[j] && demand[j] > 0 && cost[i][j] < minCost) {
                    minCost = cost[i][j];
                    best_i = i;
                    best_j = j;
                }
            }
        }
        else {
            int j = idx;
            int minCost = numeric_limits<int>::max();
            for (int i = 0; i < m; ++i) {
                if (rowActive[i] && supply[i] > 0 && cost[i][j] < minCost) {
                    minCost = cost[i][j];
                    best_i = i;
                    best_j = j;
                }
            }
        }

        int amount = min(supply[best_i], demand[best_j]);
        alloc[best_i][best_j] += amount;
        supply[best_i] -= amount;
        demand[best_j] -= amount;

        if (supply[best_i] == 0) {
            rowActive[best_i] = false;
            activeRows--;
        }
        if (demand[best_j] == 0) {
            colActive[best_j] = false;
            activeCols--;
        }
    }
    return alloc;
}

void fixDegeneracy(vector<vector<int>>& alloc, const vector<vector<int>>& cost,
    int m, int n) {
    int expected = m + n - 1;
    int basicCount = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (alloc[i][j] > 0) basicCount++;

    if (basicCount == expected) return;

    for (int i = 0; i < m && basicCount < expected; ++i) {
        for (int j = 0; j < n && basicCount < expected; ++j) {
            if (alloc[i][j] == 0) {
                alloc[i][j] = 0; // формально нулевая базисная клетка
                basicCount++;
            }
        }
    }
}

vector<pair<Cell, int>> findCycle(const vector<vector<int>>& alloc,
    int ent_i, int ent_j,
    int m, int n) {
    vector<vector<int>> adj(m + n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (alloc[i][j] > 0) {
                adj[i].push_back(m + j);
                adj[m + j].push_back(i);
            }
        }
    }
    adj[ent_i].push_back(m + ent_j);
    adj[m + ent_j].push_back(ent_i);
    adj[ent_i].pop_back();
    adj[m + ent_j].pop_back();

    vector<int> parent(m + n, -1);
    queue<int> q;
    q.push(ent_i);
    parent[ent_i] = ent_i;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        if (v == m + ent_j) break;
        for (int to : adj[v]) {
            if (parent[to] == -1) {
                parent[to] = v;
                q.push(to);
            }
        }
    }

    vector<int> pathNodes;
    int cur = m + ent_j;
    while (cur != ent_i) {
        pathNodes.push_back(cur);
        cur = parent[cur];
    }
    pathNodes.push_back(ent_i);
    reverse(pathNodes.begin(), pathNodes.end());

    vector<pair<Cell, int>> cycle;
    int sign = 1;
    for (size_t k = 0; k + 1 < pathNodes.size(); ++k) {
        int u = pathNodes[k];
        int v = pathNodes[k + 1];
        if (u < m && v >= m) { // u - строка, v - столбец
            cycle.push_back({ Cell(u, v - m, 0), sign });
        }
        else if (u >= m && v < m) {
            cycle.push_back({ Cell(v, u - m, 0), sign });
        }
        else {
        }
        sign = -sign;
    }
    cycle.push_back({ Cell(ent_i, ent_j, 0), 1 });
    return cycle;
}

void optimizePotential(vector<vector<int>>& alloc,
    const vector<vector<int>>& cost,
    vector<int>& supply, vector<int>& demand) {
    int m = M_BAL, n = N_BAL;
    bool optimal = false;
    int iter = 0;
    const int MAX_ITER = 1000;

    while (!optimal && iter < MAX_ITER) {
        iter++;
        vector<Cell> basis;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (alloc[i][j] > 0)
                    basis.emplace_back(i, j, alloc[i][j]);

        if (basis.size() != m + n - 1) {
            for (int i = 0; i < m && basis.size() < m + n - 1; ++i)
                for (int j = 0; j < n && basis.size() < m + n - 1; ++j)
                    if (alloc[i][j] == 0) {
                        basis.emplace_back(i, j, 0);
                        break;
                    }
        }

        const int INF = 1e9;
        vector<int> u(m, INF), v(n, INF);
        u[0] = 0;
        bool changed = true;
        while (changed) {
            changed = false;
            for (const Cell& cell : basis) {
                int i = cell.i, j = cell.j;
                if (u[i] != INF && v[j] == INF) {
                    v[j] = cost[i][j] - u[i];
                    changed = true;
                }
                else if (v[j] != INF && u[i] == INF) {
                    u[i] = cost[i][j] - v[j];
                    changed = true;
                }
            }
        }

        int enter_i = -1, enter_j = -1;
        int minDelta = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (alloc[i][j] > 0) continue; // только небазисные
                int delta = cost[i][j] - u[i] - v[j];
                if (delta < minDelta) {
                    minDelta = delta;
                    enter_i = i;
                    enter_j = j;
                }
            }
        }

        if (minDelta >= 0) {
            optimal = true;
            break;
        }

        auto cycle = findCycle(alloc, enter_i, enter_j, m, n);

        int theta = numeric_limits<int>::max();
        for (auto& p : cycle) {
            if (p.second == -1) {
                int i = p.first.i, j = p.first.j;
                if (alloc[i][j] < theta)
                    theta = alloc[i][j];
            }
        }

        for (auto& p : cycle) {
            int i = p.first.i, j = p.first.j;
            alloc[i][j] += p.second * theta;
        }

        for (auto& p : cycle) {
            if (p.second == -1 && alloc[p.first.i][p.first.j] == 0) {
                break;
            }
        }
    }
    if (iter == MAX_ITER)
        cout << "\nПредупреждение: достигнут лимит итераций.\n";
}

int main() {
    setlocale(LC_ALL, "rus");
    vector<int> supply_real = {
        168 + N,  // 177
        113 + N,  // 122
        150 + N,  // 159
        159 + N,  // 168
        100 + N   // 109
    };
    vector<int> demand = {
        143 + N,  // 152
        107 + N,  // 116
        131 + N,  // 140
        193 + N,  // 202
        95 + N,   // 104
        163 + N   // 172
    };

    int totalSupply = 0, totalDemand = 0;
    for (int v : supply_real) totalSupply += v;
    for (int v : demand) totalDemand += v;
    int dummySupply = totalDemand - totalSupply; // = 151

    vector<vector<int>> cost(M_BAL, vector<int>(N_BAL, 0));
    vector<vector<int>> baseCost = {
        {N + 12, N + 2, N + 6, N + 3, N + 11, N + 1},
        {N + 10, N, N + 8, N + 5, N + 7, N + 13},
        {N + 1, N + 5, N + 11, N + 8, N + 2, N + 11},
        {N + 4, N + 10, N + 10, N + 3, N + 13, N + 2},
        {N + 3, N + 11, N + 9, N, N + 10, N + 4}
    };
    for (int i = 0; i < SUPPLIERS; ++i)
        for (int j = 0; j < CONSUMERS; ++j)
            cost[i][j] = baseCost[i][j];
    for (int j = 0; j < CONSUMERS; ++j)
        cost[SUPPLIERS][j] = 0;

    vector<int> supply = supply_real;
    supply.push_back(dummySupply);

    cout << "Транспортная задача (вариант N = " << N << ")\n";
    cout << "Суммарные запасы: " << totalSupply << ", потребности: " << totalDemand
        << " -> добавляем фиктивного поставщика с запасом " << dummySupply << "\n";
    printMatrix(cost, supply, demand);

    vector<vector<int>> alloc = vogelInitial(cost, supply, demand);

    fixDegeneracy(alloc, cost, M_BAL, N_BAL);

    cout << "Начальный опорный план (метод Фогеля):\n";
    int initCost = 0;
    for (int i = 0; i < M_BAL; ++i) {
        for (int j = 0; j < N_BAL; ++j) {
            cout << setw(5) << alloc[i][j] << " ";
            initCost += alloc[i][j] * cost[i][j];
        }
        cout << "\n";
    }
    cout << "Стоимость начального плана: " << initCost << "\n\n";

    optimizePotential(alloc, cost, supply, demand);

    cout << "Оптимальный план перевозок:\n";
    int finalCost = 0;
    for (int i = 0; i < M_BAL; ++i) {
        for (int j = 0; j < N_BAL; ++j) {
            cout << setw(5) << alloc[i][j] << " ";
            finalCost += alloc[i][j] * cost[i][j];
        }
        if (i < SUPPLIERS)
            cout << " | от поставщика " << i + 1;
        else
            cout << " | фиктивный поставщик";
        cout << "\n";
    }
    cout << "\nОбщая стоимость перевозок (реальные поставщики): " << finalCost << "\n";

    vector<int> factSupply(M_BAL, 0), factDemand(N_BAL, 0);
    for (int i = 0; i < M_BAL; ++i)
        for (int j = 0; j < N_BAL; ++j) {
            factSupply[i] += alloc[i][j];
            factDemand[j] += alloc[i][j];
        }
    cout << "\nБаланс по поставщикам:\n";
    for (int i = 0; i < M_BAL; ++i) {
        cout << "Поставщик " << (i < SUPPLIERS ? to_string(i + 1) : "фиктивный") << ": "
            << factSupply[i] << " из " << supply[i] << "\n";
    }
    cout << "Баланс по потребителям:\n";
    for (int j = 0; j < N_BAL; ++j)
        cout << "Потребитель " << j + 1 << ": " << factDemand[j] << " из " << demand[j] << "\n";

    return 0;
}