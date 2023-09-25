#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "Graph.h"
#include <vector>
#include <iostream>

using namespace std;

class AdjacencyMatrixGraph : public Graph {
private:
    vector<vector<int>> matrix; 

public:
    AdjacencyMatrixGraph();
    
    void setGraphSize(int _numVertices) override;
    void addEdge(int source, int destination) override;
    void addVertex();
    vector<int> findNeighbors(int vertex) override;
    int findDegree(int vertex) override;
    void clear() override;
};

#endif // ADJACENCY_MATRIX_GRAPH_H
