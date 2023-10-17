#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <fstream>
#include <vector>
#include <list>

using namespace std;

class WeightedGraph {
public:
    WeightedGraph();

    bool readGraphFromFile(string filepath);
    void addEdge(int source, int destination, int weight);
    void addVertex();
    list<pair<int, int>> findNeighbors(int vertex);
    int getDegree(int vertex);
    void clear();

private:
    int numVertices = 0; 
    int numEdges = 0;
    vector<list<pair<int, int>>> adjacencyList;
};

#endif // WEIGHTED_GRAPH_H

