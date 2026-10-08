#include "graph.h"
#include "bfs.h"
#include "dfs.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    // Матрица смежности для графа из задания
    vector<vector<int>> matrix = {
        {0, 1, 1, 0, 0, 0, 0}, // 0 -> 1, 2
        {0, 0, 0, 0, 1, 0, 0}, // 1 -> 4
        {0, 0, 0, 1, 0, 1, 0}, // 2 -> 3, 5
        {0, 1, 0, 0, 0, 1, 1}, // 3 -> 1, 5, 6
        {0, 0, 0, 0, 0, 0, 1}, // 4 -> 6
        {0, 0, 0, 0, 0, 0, 1}, // 5 -> 6
        {0, 0, 0, 0, 0, 0, 0}  // 6 ->
    };

    // Создаем граф
    OrientedGraph g(matrix);


    g.printAdjMatrix();
    cout << endl;
    g.printAdjList();

    // BFS
    runBFS(g, 0);

    // DFS
    runDFS(g, 0);

    // Топологическая сортировка
    runTopologicalSort(g);

    return 0;
}