#include "MatrixGraph.h"

MatrixGraph::MatrixGraph( int vertexCount ){
    assert( vertexCount > 0 );
    adjLists.resize( vertexCount );
    for( int i = 0; i < vertexCount; ++i ){
        adjLists[i].resize( vertexCount );
    }
}

MatrixGraph::MatrixGraph( const IGraph& graph ){
    adjLists.resize( graph.VerticesCount() );
    for( int i = 0; i < graph.VerticesCount(); ++i ){
        adjLists[i].resize( graph.VerticesCount() );
        std::vector<int> next = graph.GetNextVertices( i );
        for( int j = 0; j < next.size(); ++j ){
            adjLists[i][next[j]] = 1;
        }
    }
}

void MatrixGraph::AddEdge( int from, int to ){
    assert( from >= 0 && from < adjLists.size() );
    assert( to >= 0 && to < adjLists.size() );
    adjLists[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return adjLists.size();
}

std::vector<int> MatrixGraph::GetNextVertices( int vertex ) const {
    assert( vertex >= 0 && vertex < adjLists.size() );
    std::vector<int> next;
    for( int i = 0; i < adjLists.size(); ++i ){
        if( adjLists[vertex][i] == 1 ) next.push_back( i );
    }
    return next;
}

std::vector<int> MatrixGraph::GetPrevVertices( int vertex ) const {
    assert( vertex >= 0 && vertex < adjLists.size() );
    std::vector<int> prev;
    for( int i = 0; i < adjLists.size(); ++i ){
        if( adjLists[i][vertex] == 1 ) prev.push_back( i );
    }
    return prev;
}