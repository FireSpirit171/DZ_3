/* Задача 5 Вариант 2
 * Найдите приближенное решение метрической неориентированной задачи коммивояжера в полном графе (на плоскости) с помощью минимального остовного дерева.
 * Для построения минимального остовного дерева используйте алгоритм Прима.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>

struct Edge {
  Edge(size_t from, size_t to, size_t weight) : from(from), to(to), weight(weight) {}

  bool operator>(const Edge& edge) const {
    return weight > edge.weight;
  }

  size_t from;
  size_t to;
  size_t weight;
};

int primMST(const std::vector<std::vector<std::pair<size_t, size_t>>>& adjList, size_t vertexCount) {
  std::vector<bool> inMST(vertexCount, false);
  std::priority_queue<Edge, std::vector<Edge>, std::greater<>> pq;

  size_t startVertex = 0;
  inMST[startVertex] = true;

  for (const auto& neighbor : adjList[startVertex]) {
    pq.emplace(startVertex, neighbor.first, neighbor.second);
  }

  int totalWeight = 0;
  while (!pq.empty()) {
    Edge minEdge = pq.top();
    pq.pop();

    if (inMST[minEdge.to]) continue;

    inMST[minEdge.to] = true;
    totalWeight += minEdge.weight;

    for (const auto& neighbor : adjList[minEdge.to]) {
      if (!inMST[neighbor.first]) {
        pq.emplace(minEdge.to, neighbor.first, neighbor.second);
      }
    }
  }

  return totalWeight;
}

int main() {
  size_t vertexCount, edgeCount;
  std::cin >> vertexCount >> edgeCount;

  std::vector<std::vector<std::pair<size_t, size_t>>> adjList(vertexCount);

  size_t from, to, weight;
  for (size_t i = 0; i < edgeCount; ++i) {
    std::cin >> from >> to >> weight;
    from--; // корректировка индекса для вектора adjLists
    to--;   // корректировка индекса для вектора adjLists
    adjList[from].emplace_back(to, weight);
    adjList[to].emplace_back(from, weight);
  }

  std::cout << primMST(adjList, vertexCount) << std::endl;

  return 0;
}
