#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include "FibonacciHeap.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <climits>
#include <iomanip>
#include <queue>
#include <unordered_map>

using namespace std;

#define INFINITY_FLOAT numeric_limits<float>::max()

// Struct to store the result of Dijkstra search
struct DijkstraResult {
    vector<int> parent;
    vector<float> distance;
};

class WeightedGraph {
private:
    int numVertices = 0; 
    int numEdges = 0;
    bool negativeWeight = false;
    bool isDirected;
    vector<list<pair<int, float>>> adjacencyList;

    void addEdge(int source, int destination, float weight);
    void deleteEdge(int source, int destination);
    void addVertex();
    list<pair<int, float>> findNeighbors(int vertex);
    int findDegree(int vertex);
    bool findAugmentingPath(int source, int sink, vector<int>& parent);
    int getResidualCapacity(int startEdge, int endEdge);
    void updateResidualCapacity(int startEdge, int endEdge, int flow);
    void clear();

public:
    WeightedGraph(bool isDirected = false);
    WeightedGraph(const WeightedGraph &other);
    bool readGraphFromFile(string filepath);
    pair<float, list<int>> shortestPath(int source, int destination, bool heap = true);
    DijkstraResult dijkstraVector(int source, int destination = -1);
    DijkstraResult dijkstraHeap(int source, int destination = -1);
    int fordFulkerson(int source, int sink);
    int getNumVertices();
    int getNumEdges();
};

#endif // WEIGHTED_GRAPH_H

