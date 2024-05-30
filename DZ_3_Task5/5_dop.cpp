/* Вывод для N = 10
 * For N = 2, Mean Approximation Ratio = 1, Standard Deviation = 0
 * For N = 3, Mean Approximation Ratio = 1, Standard Deviation = 0
 * For N = 4, Mean Approximation Ratio = 1, Standard Deviation = 0
 * For N = 5, Mean Approximation Ratio = 1.00168, Standard Deviation = 1.97096e-008
 * For N = 6, Mean Approximation Ratio = 1.00168, Standard Deviation = 6.34223e-009
 * For N = 7, Mean Approximation Ratio = 1.30829, Standard Deviation = 3.99221e-009
 * For N = 8, Mean Approximation Ratio = 1.37298, Standard Deviation = 0.0751979
 * For N = 9, Mean Approximation Ratio = 1.59363, Standard Deviation = 0.225673
 * For N = 10, Mean Approximation Ratio = 1.78111, Standard Deviation = 0.317052
*/


#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <functional>
#include <utility>
#include <algorithm>
#include <numeric>
#include <limits>
#include <ctime>
#include <cstdlib>

const double PI = 3.14;

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

  for (size_t i = 0; i < adjList[startVertex].size(); ++i) {
    pq.emplace(startVertex, adjList[startVertex][i].first, adjList[startVertex][i].second);
  }

  int totalWeight = 0;
  while (!pq.empty()) {
    Edge minEdge = pq.top();
    pq.pop();

    if (inMST[minEdge.to]) continue;

    inMST[minEdge.to] = true;
    totalWeight += minEdge.weight;

    for (size_t i = 0; i < adjList[minEdge.to].size(); ++i) {
      size_t v = adjList[minEdge.to][i].first;
      size_t weight = adjList[minEdge.to][i].second;
      if (!inMST[v]) {
        pq.emplace(minEdge.to, v, weight);
      }
    }
  }

  return totalWeight;
}

//Генерация случайных точек
std::vector<std::pair<double, double>> generateRandomPoints(size_t N) {
  std::vector<std::pair<double, double>> points;
  std::srand(std::time(0));

  for (size_t i = 0; i < N; ++i) {
    double u1 = ((double)std::rand() / RAND_MAX);
    double u2 = ((double)std::rand() / RAND_MAX);
    double r = std::sqrt(-2 * std::log(u1));
    double theta = 2 * PI * u2;
    double x = r * std::cos(theta);
    double y = r * std::sin(theta);
    points.emplace_back(x, y);
  }

  return points;
}

//Построение полного графа
std::vector<std::vector<std::pair<size_t, size_t>>> buildCompleteGraph(const std::vector<std::pair<double, double>>& points) {
  size_t N = points.size();
  std::vector<std::vector<std::pair<size_t, size_t>>> adjList(N);

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = i + 1; j < N; ++j) {
      double dist = std::hypot(points[i].first - points[j].first, points[i].second - points[j].second);
      size_t weight = static_cast<size_t>(dist * 1000); // Умножаем на 1000 для избежания работы с плавающей запятой
      adjList[i].emplace_back(j, weight);
      adjList[j].emplace_back(i, weight);
    }
  }

  return adjList;
}

double calculateTourLength(const std::vector<std::pair<double, double>>& points, const std::vector<size_t>& tour) {
  double totalLength = 0.0;
  for (size_t i = 0; i < tour.size(); ++i) {
    size_t from = tour[i];
    size_t to = tour[(i + 1) % tour.size()];
    totalLength += std::hypot(points[from].first - points[to].first, points[from].second - points[to].second);
  }
  return totalLength;
}

//Приближенное нахождение
std::vector<size_t> findApproximateTSPTour(const std::vector<std::pair<double, double>>& points) {
  size_t N = points.size();
  auto adjList = buildCompleteGraph(points);
  primMST(adjList, N);

  std::vector<bool> visited(N, false);
  std::vector<size_t> tour;

  std::function<void(size_t)> dfs = [&](size_t u) {
    visited[u] = true;
    tour.push_back(u);
    for (size_t i = 0; i < adjList[u].size(); ++i) {
      size_t v = adjList[u][i].first;
      size_t weight = adjList[u][i].second;
      if (!visited[v]) {
        dfs(v);
      }
    }
  };

  dfs(0); // Начинаем обход с первой вершины

  return tour;
}

//Полный перебор
double findOptimalTourLength(const std::vector<std::pair<double, double>>& points) {
  size_t N = points.size();
  std::vector<size_t> vertices(N);
  for (size_t i = 0; i < N; ++i) {
    vertices[i] = i;
  }

  double minTourLength = std::numeric_limits<double>::max();

  do {
    double currentTourLength = calculateTourLength(points, vertices);
    if (currentTourLength < minTourLength) {
      minTourLength = currentTourLength;
    }
  } while (std::next_permutation(vertices.begin(), vertices.end()));

  return minTourLength;
}

//Вывод необходимых значений
void evaluateApproximation(size_t N, size_t numTrials) {
  std::vector<double> ratios;
  for (size_t i = 0; i < numTrials; ++i) {
    auto points = generateRandomPoints(N);
    auto approxTour = findApproximateTSPTour(points);
    double approxLength = calculateTourLength(points, approxTour);
    double optimalLength = findOptimalTourLength(points);

    double ratio = approxLength / optimalLength;
    ratios.push_back(ratio);
  }

  double meanRatio = 0.0;
  for (size_t i = 0; i < ratios.size(); ++i) {
    meanRatio += ratios[i];
  }
  meanRatio /= ratios.size();

  double sq_sum = 0.0;
  for (size_t i = 0; i < ratios.size(); ++i) {
    sq_sum += ratios[i] * ratios[i];
  }
  double stddev = std::sqrt(sq_sum / ratios.size() - meanRatio * meanRatio);

  std::cout << "For N = " << N << ", Mean Approximation Ratio = " << meanRatio << ", Standard Deviation = " << stddev << std::endl;
}

int main() {
  for (size_t N = 2; N <= 10; ++N) {
    evaluateApproximation(N, 10); // Запускаем эксперимент для каждого N от 2 до 10 с 10 испытаниями
  }

  return 0;
}
