#include "SetGraph.h"

SetGraph::SetGraph(int vertexCount) {
    assert(vertexCount > 0);
    adjSets.resize(vertexCount);
    prevAdjSets.resize(vertexCount);
}

SetGraph::SetGraph(const IGraph& graph) {
    int vertexCount = graph.VerticesCount();
    adjSets.resize(vertexCount);
    prevAdjSets.resize(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int next : nextVertices) {
            adjSets[i].insert(next);
        }
        std::vector<int> prevVertices = graph.GetPrevVertices(i);
        for (int prev : prevVertices) {
            prevAdjSets[i].insert(prev);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjSets.size());
    assert(to >= 0 && to < adjSets.size());
    adjSets[from].insert(to);
    prevAdjSets[to].insert(from);
}

int SetGraph::VerticesCount() const {
    return adjSets.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjSets.size());
    return std::vector<int>(adjSets[vertex].begin(), adjSets[vertex].end());
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < prevAdjSets.size());
    return std::vector<int>(prevAdjSets[vertex].begin(), prevAdjSets[vertex].end());
}