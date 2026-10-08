#include "graph.h"
#include <vector>

using namespace std;

OrientedGraph::OrientedGraph(const vector<vector<int>>& matrix) {
    n = matrix.size();
    adjList.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                adjList[i].push_back(j);
            }
        }
    }
}

OrientedGraph::OrientedGraph(int vertices, const vector<vector<int>>& list) {
    n = vertices;
    adjList = list;
}

vector<vector<int>> OrientedGraph::toAdjMatrix() const {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int v : adjList[i]) {
            matrix[i][v] = 1;
        }
    }
    return matrix;
}

void OrientedGraph::printAdjList() const {
    cout << "Список смежности (исходящие дуги):" << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int v : adjList[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

void OrientedGraph::printAdjMatrix() const {
    vector<vector<int>> matrix = toAdjMatrix();
    cout << "Матрица смежности:" << endl;
    cout << "   ";
    for (int j = 0; j < n; j++) cout << j << " ";
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << i << "  ";
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}