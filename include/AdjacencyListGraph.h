#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "Graph.h"
#include <vector>
#include <list>

using namespace std;

class AdjacencyListGraph : public Graph {
private:
    vector<list<int>> adjacencyList;

public:
    AdjacencyListGraph();

    void setGraphSize(int _numVertices) override;
    void addEdge(int source, int destination) override;
    void addVertex();
    vector<int> findNeighbors(int vertex) override;
    int findDegree(int vertex) override;
    void clear() override;
};

#endif // ADJACENCY_LIST_GRAPH_H
