#include "WeightedGraph.h"

WeightedGraph::WeightedGraph() {
}

bool WeightedGraph::readGraphFromFile(string filepath) {
    clear(); // Clear any previous graph

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
    }

    file.close();
    return true; // Graph read succesfully
}

void WeightedGraph::addEdge(int source, int destination, int weight) {
    // Add a weighted edge from 'source' to 'destination' with the specified weight
    adjacencyList[source-1].push_back(make_pair(destination, weight));
    numEdges++;
}

void WeightedGraph::addVertex() {
    // Add a new vertex to the graph
    adjacencyList.push_back(list<pair<int, int>>());
    numVertices++;
}

list<pair<int, int>> WeightedGraph::findNeighbors(int vertex) {
    // Return the list of neighbors with their respective weights
    if (vertex > 0 && vertex <= numVertices) {
        return adjacencyList[vertex - 1];
    } else {
        return list<pair<int, int>>();
    }
}

int WeightedGraph::getDegree(int vertex) {
    // Find the degree (number of neighbors) of the specified vertex
    if (vertex > 0 && vertex <= numVertices) {
        return adjacencyList[vertex - 1].size();
    } else {
        return 0;
    }
}

void WeightedGraph::clear() {
    adjacencyList.clear();
    numVertices = 0;
    numEdges = 0;
}