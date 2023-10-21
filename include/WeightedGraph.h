#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include "FibonacciHeap.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <climits>
#include <unordered_map>

using namespace std;

// Struct to store the result of Dijkstra search
struct DijkstraResult {
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
    DijkstraResult dijkstraVector(int source, int destination = INT_MAX);
    DijkstraResult dijkstraHeap(int source, int destination = INT_MAX);
    pair<int, list<int>> shortestPath(int source, int destination, bool heap = true);
    void clear();

private:
    int numVertices = 0; 
    int numEdges = 0;
    bool negativeWeight = false;
    vector<list<pair<int, int>>> adjacencyList;
};

#endif // WEIGHTED_GRAPH_H

