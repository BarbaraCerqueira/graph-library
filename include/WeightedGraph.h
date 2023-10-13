#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class WeightedGraph {
public:
    WeightedGraph();

    bool readGraphFromFile(string filepath);
    void addEdge(int from, int to, int weight);
    void clear();

private:
    int numVertices = 0; 
    int numEdges = 0;
    vector<vector<pair<int, int>>> adjacencyList;
};

#endif // WEIGHTED_GRAPH_H
