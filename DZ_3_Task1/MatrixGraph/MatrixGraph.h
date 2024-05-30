#include "../IGraph/IGraph.h"
#include <cassert>

class MatrixGraph : public IGraph {
private:
    std::vector<std::vector<int>> adjLists;

public:
    MatrixGraph( int );
    MatrixGraph( const IGraph& );
    
    virtual void AddEdge( int, int ) override;
    virtual int VerticesCount() const override;
    virtual std::vector<int> GetNextVertices( int ) const override;
    virtual std::vector<int> GetPrevVertices( int ) const override;
};