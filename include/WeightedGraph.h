#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include "FibonacciHeap.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <climits>
#include <iomanip>
#include <unordered_map>

using namespace std;

#define INFINITY_FLOAT numeric_limits<float>::max()

// Struct to store the result of Dijkstra search
struct DijkstraResult {
    vector<int> parent;
    vector<float> distance;
};

class WeightedGraph {
public:
    WeightedGraph();

    bool readGraphFromFile(string filepath);
    void addEdge(int source, int destination, float weight);
    void addVertex();
    list<pair<int, float>> findNeighbors(int vertex);
    int findDegree(int vertex);
    DijkstraResult dijkstraVector(int source, int destination = -1);
    DijkstraResult dijkstraHeap(int source, int destination = -1);
    pair<float, list<int>> shortestPath(int source, int destination, bool heap = true);
    int getNumVertices();
    int getNumEdges();
    void clear();

private:
    int numVertices = 0; 
    int numEdges = 0;
    bool negativeWeight = false;
    vector<list<pair<int, float>>> adjacencyList;
};

#endif // WEIGHTED_GRAPH_H

