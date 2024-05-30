#include "ArcGraph.h"

ArcGraph::ArcGraph( int vertexCount ){
    assert( vertexCount > 0 );
    adjLists.resize( vertexCount );
}

ArcGraph::ArcGraph( const IGraph& graph ){
    adjLists.resize( graph.VerticesCount() );
    for( int i = 0; i < graph.VerticesCount(); ++i ){
        std::vector<int> next = graph.GetNextVertices( i );
        for( int j = 0; j < next.size(); ++j ){
            std::pair<int, int> edge(i, next[j]);
            adjLists.push_back( edge );
        }
    }
}

void ArcGraph::AddEdge( int from, int to ){
    std::pair<int, int> edge( from, to );
    adjLists.push_back( edge );
}

int ArcGraph::VerticesCount() const {
    std::set<int> vertices;
    for( int i = 0; i < adjLists.size(); ++i ){
        vertices.insert(adjLists[i].first);
        vertices.insert(adjLists[i].second);
    }
    return vertices.size();
}

std::vector<int> ArcGraph::GetNextVertices( int vertex ) const {
    std::vector<int> next;
    for( int i = 0; i < adjLists.size(); ++i ){
        if( adjLists[i].first == vertex ) next.push_back( adjLists[i].second );
    }
    return next;
}

std::vector<int> ArcGraph::GetPrevVertices( int vertex ) const {
    std::vector<int> prev;
    for( int i = 0; i < adjLists.size(); ++i ){
        if( adjLists[i].second == vertex ) prev.push_back( adjLists[i].first );
    }
    return prev;
}