#include "../IGraph/IGraph.h"
#include <cassert>

class ListGraph : public IGraph {
private:
    std::vector<std::vector<int>> adjLists;
    std::vector<std::vector<int>> prevAdjLists;

public:
    ListGraph( int );
    ListGraph( const IGraph& );
    
    virtual void AddEdge( int, int ) override;
    virtual int VerticesCount() const override;
    virtual std::vector<int> GetNextVertices( int ) const override;
    virtual std::vector<int> GetPrevVertices( int ) const override;
};