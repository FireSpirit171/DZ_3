#include "../IGraph/IGraph.h"
#include <cassert>
#include <set>
#include <utility>

class ArcGraph : public IGraph {
private:
    std::vector<std::pair<int, int>> adjLists;

public:
    ArcGraph( int );
    ArcGraph( const IGraph& );
    
    virtual void AddEdge( int, int ) override;
    virtual int VerticesCount() const override;
    virtual std::vector<int> GetNextVertices( int ) const override;
    virtual std::vector<int> GetPrevVertices( int ) const override;
};