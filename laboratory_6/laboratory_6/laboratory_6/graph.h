#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

class OrientedGraph {
private:
    int n; // количество вершин
    std::vector<std::vector<int>> adjList; // список смежности

public:
    // Конструктор из матрицы смежности
    OrientedGraph(const std::vector<std::vector<int>>& matrix);

    // Конструктор из списка смежности
    OrientedGraph(int vertices, const std::vector<std::vector<int>>& list);

    // Преобразование списка смежности в матрицу смежности
    std::vector<std::vector<int>> toAdjMatrix() const;

    // Вывод списка смежности
    void printAdjList() const;

    // Вывод матрицы смежности
    void printAdjMatrix() const;

    // Получение списка смежности (для использования в алгоритмах)
    const std::vector<std::vector<int>>& getAdjList() const { return adjList; }

    // Получение количества вершин
    int getVertexCount() const { return n; }
};

#endif