#pragma once
#include <vector>
#include "Combi.h"

namespace tspfuncs {
    const int INF = 1000000; // "бесконечное" рассто€ние

    // ¬озвращает минимальную длину гамильтонова цикла (задача коммиво€жера)
    // и заполн€ет bestRoute пор€дком городов (начина€ с 0)
    int tsp(int n, const std::vector<std::vector<int>>& dist, std::vector<int>& bestRoute);
}