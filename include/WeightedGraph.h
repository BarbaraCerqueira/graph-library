#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <climits>

using namespace std;

// Struct to store the result of Dijkstra search
struct SearchResult {
    vector<bool> visited;
    vector<int> parent;
    vector<int> distance;
};

class WeightedGraph {
public:
    WeightedGraph();

    bool readGraphFromFile(string filepath);
    void addEdge(int source, int destination, int weight);
    void addVertex();
    list<pair<int, int>> findNeighbors(int vertex);
    int findDegree(int vertex);
    SearchResult dijkstraVector(int source, int destination);
    SearchResult dijkstraHeap(int source, int destination);
    void clear();

private:
    int numVertices = 0; 
    int numEdges = 0;
    vector<list<pair<int, int>>> adjacencyList;
};

#endif // WEIGHTED_GRAPH_H

