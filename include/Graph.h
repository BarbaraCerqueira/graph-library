#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

class Graph {
protected:
    int numVertices;
    int numEdges;

    virtual void addEdge(int source, int destination) = 0;
    virtual void setGraphSize(int _numVertices) = 0;
    virtual vector<int> findNeighbors(int vertex) = 0;
    virtual int findDegree(int vertex) = 0;
    virtual void clear();

public:
    Graph();
    bool readGraphFromFile(string filepath);
    void showVariables();
    void BFS(int startVertex);
    void DFS(int startVertex);
};

#endif // GRAPH_H
