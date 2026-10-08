#include "tcp.h"
#include <algorithm>
#include <climits>

namespace tspfuncs {

    
    int calculateDistance(const std::vector<int>& route, const std::vector<std::vector<int>>& dist) {
        int total = 0;
        int n = route.size();
        for (int i = 0; i < n - 1; ++i) {
            int d = dist[route[i]][route[i + 1]];
            if (d >= INF) return INF;
            total += d;
        }
        int d = dist[route[n - 1]][route[0]];
        if (d >= INF) return INF;
        total += d;
        return total;
    }

    int tsp(int n, const std::vector<std::vector<int>>& dist, std::vector<int>& bestRoute) {
        if (n <= 1) return 0;

        combi::permutation p(n - 1);
        long long count = p.getfirst();
        int minDist = INF;
        bestRoute.clear();
//
        while (count >= 0) {
            
            std::vector<int> route;
            route.push_back(0);
            for (int i = 0; i < n - 1; ++i) {
                route.push_back(p.ntx(i) + 1);
            }

            int d = calculateDistance(route, dist);
            if (d < minDist) {
                minDist = d;
                bestRoute = route;
            }

            count = p.getnext();
        }

        return minDist;
    }

}