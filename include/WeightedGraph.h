#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <climits>

using namespace std;

class WeightedGraph {
public:
    WeightedGraph();

    bool readGraphFromFile(string filepath);
    void addEdge(int source, int destination, int weight);
    void addVertex();
    vector<pair<int, int>> findNeighbors(int vertex);
    int findDegree(int vertex);
    vector<pair<int, int>> dijkstra(int source);
    void clear();

private:
    int numVertices = 0; 
    int numEdges = 0;
    vector<list<pair<int, int>>> adjacencyList;
};

#endif // WEIGHTED_GRAPH_H

