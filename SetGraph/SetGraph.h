#include "../IGraph/IGraph.h"
#include <cassert>
#include <set>

class SetGraph : public IGraph {
private:
    std::vector<std::set<int>> adjSets;
    std::vector<std::set<int>> prevAdjSets;

public:
    SetGraph(int vertexCount);
    SetGraph(const IGraph& graph);

    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const override;
    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;
};