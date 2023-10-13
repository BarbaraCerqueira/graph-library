#ifndef UNWEIGHTED_GRAPH_H
#define UNWEIGHTED_GRAPH_H

#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <omp.h>

using namespace std;

// Struct to store the result of BFS and DFS
struct SearchResult {
    vector<bool> visited;
    vector<int> parent;
    vector<int> level;
};

class UnweightedGraph {
protected:
    int numVertices = 0;
    int numEdges = 0;

    virtual void addEdge(int source, int destination) = 0;
    virtual void setGraphSize(int _numVertices) = 0;
    virtual vector<int> findNeighbors(int vertex) = 0;
    virtual int findDegree(int vertex) = 0;
    virtual void clear();

    void writeTreeToFile(int startVertex, 
                        const vector<int>& parent, 
                        const vector<int>& level, 
                        string searchName);
    vector<int> getSortedVertexDegrees();

public:
    UnweightedGraph();
    virtual ~UnweightedGraph() {};
    bool readGraphFromFile(string filepath);
    SearchResult BFS(int startVertex, bool outputToFile = true);
    SearchResult DFS(int startVertex, bool outputToFile = true);
    vector<vector<int>> findConnectedComponents();
    int shortestDistance(int source, int destination);
    int diameter();
    int estimateDiameter();
    void generateGraphInfoFile();
    int getNumVertices();
    
};

#endif // UNWEIGHTED_GRAPH_H
