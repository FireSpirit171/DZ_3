#include "ListGraph/ListGraph.h"
#include "MatrixGraph/MatrixGraph.h"
#include "SetGraph/SetGraph.h"
#include "ArcGraph/ArcGraph.h"
#include <queue>
#include <iostream>

void BFS(const IGraph& graph, int vertex, void(*visit)(int)) {
    std::vector<bool> visited(graph.VerticesCount());
    std::queue<int> bfs;
    bfs.push(vertex);
    visited[vertex] = true;
    while (!bfs.empty()) {
        int current = bfs.front();
        bfs.pop();
        visit(current);

        std::vector<int> next = graph.GetNextVertices(current);
        for (int i = 0; i < next.size(); ++i) {
            if (!visited[next[i]]) {
                bfs.push(next[i]);
                visited[next[i]] = true;
            }
        }
    }
}

void TestGraph( const ListGraph& listGraph, const MatrixGraph& matrixGraph, const SetGraph& setGraph, const ArcGraph& arcGraph, int startVertex ){
    BFS(listGraph, startVertex, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    BFS(matrixGraph, startVertex, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    BFS(setGraph, startVertex, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    BFS(arcGraph, startVertex, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
}

//Тест 1 - граф с семинара
void Test1() {
    std::cout << "Test 1: Specific Graph" << std::endl;
    ListGraph listGraph(8);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 4);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(2, 5);
    listGraph.AddEdge(3, 0);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(4, 6);
    listGraph.AddEdge(5, 3);
    listGraph.AddEdge(6, 3);
    listGraph.AddEdge(6, 5);
    listGraph.AddEdge(6, 7);
    listGraph.AddEdge(7, 5);

    MatrixGraph matrixGraph(listGraph);
    SetGraph setGraph(matrixGraph);
    ArcGraph arcGraph(setGraph);

    TestGraph( listGraph, matrixGraph, setGraph, arcGraph, 4 );
}

//Тест 2 - полный граф на 5 вершинах
void Test2() {
    std::cout << "Test 2: Complete Graph" << std::endl;
    int vertexCount = 5;
    MatrixGraph matrixGraph(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            if (i != j) {
                matrixGraph.AddEdge(i, j);
            }
        }
    }

    ListGraph listGraph(matrixGraph);
    ArcGraph arcGraph(listGraph);
    SetGraph setGraph(arcGraph);

    TestGraph( listGraph, matrixGraph, setGraph, arcGraph, 3 );
}

//Тест 3 - слабо связанный граф из 20 вершин
void Test3() {
    std::cout << "Test 3: Weakly Connected Graph" << std::endl;
    int vertexCount = 20;
    SetGraph setGraph(vertexCount);
    for (int i = 0; i < vertexCount - 1; ++i) {
        setGraph.AddEdge(i, i + 1);
    }

    ListGraph listGraph(setGraph);
    ArcGraph arcGraph(listGraph);
    MatrixGraph matrixGraph(arcGraph);

    TestGraph( listGraph, matrixGraph, setGraph, arcGraph, 0 );
}

int main() {
    Test1();
    Test2();
    Test3();

    return 0;
}
