#include "bfs.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

void runBFS(const OrientedGraph& g, int start) {
    int n = g.getVertexCount();
    const auto& adjList = g.getAdjList();

    vector<int> color(n, 0); // 0-white, 1-gray, 2-black
    vector<int> dist(n, -1);
    vector<int> parent(n, -1);
    queue<int> q;

    color[start] = 1;
    dist[start] = 0;
    q.push(start);

    cout << "\nBFS от вершины " << start << endl;
    cout << "Порядок обхода: ";

    int step = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        color[u] = 2;
        cout << u << " ";

        cout << "\n  Шаг " << step++ << ": извлекаем " << u << endl;

        for (int v : adjList[u]) {
            if (color[v] == 0) {
                color[v] = 1;
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
                cout << "    -> добавляем " << v << " (расстояние " << dist[v] << ", parent=" << u << ")" << endl;
            }
        }
    }
    cout << "\n\nРезультаты BFS:" << endl;
    cout << "Вершина: ";
    for (int i = 0; i < n; i++) cout << i << " ";
    
}