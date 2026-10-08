#include "dfs.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
 
// Рекурсивная DFS для обхода
void dfsVisit(int u, vector<int>& color, const vector<vector<int>>& adjList, vector<int>& order) {
    color[u] = 1; // серый
    order.push_back(u);

    for (int v : adjList[u]) {
        if (color[v] == 0) {
            dfsVisit(v, color, adjList, order);
        }
    }
    color[u] = 2; // черный
}

void runDFS(const OrientedGraph& g, int start) {
    int n = g.getVertexCount();
    const auto& adjList = g.getAdjList();

    vector<int> color(n, 0);
    vector<int> order;

    cout << "\nDFS от вершины " << start << endl;

    dfsVisit(start, color, adjList, order);

    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfsVisit(i, color, adjList, order);
        }
    }

    cout << "Порядок обхода: ";
    for (int v : order) cout << v << " ";
    cout << endl;
}

// DFS для топологической сортировк
bool dfsTopo(int u, vector<int>& color, const vector<vector<int>>& adjList, vector<int>& result) {
    color[u] = 1; 

    for (int v : adjList[u]) {
        if (color[v] == 1) {
                        return true;
        }
        if (color[v] == 0) {
            if (dfsTopo(v, color, adjList, result)) {
                return true;
            }
        }
    }

    color[u] = 2; 
    result.push_back(u);
    return false;
}


void runTopologicalSort(const OrientedGraph& g) {
    int n = g.getVertexCount();
    const auto& adjList = g.getAdjList();

    vector<int> color(n, 0);
    vector<int> result;
    bool hasCycle = false;

    cout << "\nТопологическая сортировка (через DFS)" << endl;

    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (dfsTopo(i, color, adjList, result)) {
                hasCycle = true;
                break;
            }
        }
    }

    if (hasCycle) {
        cout << "РЕЗУЛЬТАТ: Топологическая сортировка НЕВОЗМОЖНА (граф содержит цикл)" << endl;
    }
    else {
        reverse(result.begin(), result.end());
        cout << "Порядок: ";
        for (int v : result) cout << v << " ";
        cout << endl;


    }
}