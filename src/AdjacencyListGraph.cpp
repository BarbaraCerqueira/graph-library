#include "AdjacencyListGraph.h"


AdjacencyListGraph::AdjacencyListGraph() : UnweightedGraph() {
}

void AdjacencyListGraph::setGraphSize(int _numVertices) {
    adjacencyList.resize(_numVertices);
}

void AdjacencyListGraph::addEdge(int source, int destination) {
    if (source > 0 && source <= numVertices && destination > 0 && destination <= numVertices) {
        adjacencyList[source - 1].push_back(destination);
        adjacencyList[destination - 1].push_back(source);
    } else {
        cout << "Invalid vertices!" << endl;
    }
}

void AdjacencyListGraph::addVertex() {
    numVertices++;
    adjacencyList.push_back(list<int>());
}

vector<int> AdjacencyListGraph::findNeighbors(int vertex) {
    vector<int> neighbors;
    if (vertex > 0 && vertex <= numVertices) {
        for (int neighbor : adjacencyList[vertex - 1]) {
            neighbors.push_back(neighbor);
        }
    } else {
        cout << "Invalid vertex!" << endl;
    }
    return neighbors;
}

int AdjacencyListGraph::findDegree(int vertex) {
    if (vertex > 0 && vertex <= numVertices) {
        return adjacencyList[vertex - 1].size();
    } else {
        cout << "Invalid vertex!" << endl;
        return -1;
    }
}

void AdjacencyListGraph::clear() {
    adjacencyList.clear();
    UnweightedGraph::clear();
}



