#include <iostream>

int main() {
    std::cout << "digraph BranchAndBound {\n";
    std::cout << "    // Узлы\n";
    std::cout << "    root [label=\"Корень\\nНГ=83\", shape=box];\n";
    std::cout << "    A [label=\"Вкл (5,4)\\nНГ=87\", shape=box];\n";
    std::cout << "    B [label=\"Вкл (1,5)\\nНГ=89\", shape=box];\n";
    std::cout << "    C [label=\"Вкл (4,3)\\nРешение\\nстоимость=89\", shape=box, style=filled, fillcolor=lightgreen];\n";
    std::cout << "    D [label=\"Искл (4,3)\\nНГ=117\\nотсечено\", shape=box, style=dashed];\n";
    std::cout << "    E [label=\"Искл (1,5)\\nНГ=113\\nотсечено\", shape=box, style=dashed];\n";
    std::cout << "    F [label=\"Искл (5,4)\\nНГ=101\\nотсечено\", shape=box, style=dashed];\n";
    std::cout << "\n    // Рёбра\n";
    std::cout << "    root -> A [label=\"включение (5,4)\"];\n";
    std::cout << "    root -> F [label=\"исключение (5,4)\"];\n";
    std::cout << "    A -> B [label=\"включение (1,5)\"];\n";
    std::cout << "    A -> E [label=\"исключение (1,5)\"];\n";
    std::cout << "    B -> C [label=\"включение (4,3)\"];\n";
    std::cout << "    B -> D [label=\"исключение (4,3)\"];\n";
    std::cout << "}\n";
    return 0;
}