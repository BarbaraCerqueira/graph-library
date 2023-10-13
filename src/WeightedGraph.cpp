#include "WeightedGraph.h"

WeightedGraph::WeightedGraph() {
}

bool WeightedGraph::readGraphFromFile(string filepath) {
    clear();

    ifstream file(filepath);
    if (!file.is_open()) {
        return false; // Error trying to open file
    }

    // Reads number of vertices and adjusts structure
    file >> numVertices;
    adjacencyList.resize(numVertices);

    int source, destination, weight;
    while (file >> source >> destination >> weight) {
        addEdge(source, destination, weight);
        numEdges++;
    }

    file.close();
    return true; // Graph read succesfully
}

void WeightedGraph::addEdge(int source, int destination, int weight) {
    // Add a weighted edge from 'source' to 'destination' with the specified weight
    adjacencyList[source].push_back(make_pair(destination, weight));
}

void WeightedGraph::clear() {
    adjacencyList.clear();
    numVertices = 0;
    numEdges = 0;
}