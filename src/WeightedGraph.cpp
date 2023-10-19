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

vector<pair<int, int>> WeightedGraph::findNeighbors(int vertex) {
    // Return the list of neighbors with their respective weights
    vector<pair<int, int>> neighbors;
    if (vertex > 0 && vertex <= numVertices) {
        for (pair<int, int> neighbor : adjacencyList[vertex - 1]) {
            neighbors.push_back(neighbor);
        }
    } else {
        cout << "Invalid vertex!" << endl;
    }
    return neighbors;
}

int WeightedGraph::findDegree(int vertex) {
    // Find the degree (number of neighbors) of the specified vertex
    if (vertex > 0 && vertex <= numVertices) {
        return adjacencyList[vertex - 1].size();
    } else {
        cout << "Invalid vertex!" << endl;
        return -1;
    }
}

vector<pair<int, int>> WeightedGraph::dijkstra(int vertex) {
    vector<int> distance(numVertices, INT_MAX);
    vector<int> parent(numVertices, -1);
    
    // Set the distance of the source vertex to 0
    distance[vertex - 1] = 0;
    
    // Create a set to keep track of unvisited vertices
    set<pair<int, int>> unvisited;  // (distance, vertex)
    for (int i = 1; i <= numVertices; i++) {
        unvisited.insert({distance[i - 1], i});
    }
    
    vector<pair<int, int>> minSpanningTree;  // To store the resulting minimum spanning tree
    
    while (!unvisited.empty()) {
        int u = unvisited.begin()->second;
        unvisited.erase(unvisited.begin());
        
        if (parent[u - 1] != -1) {
            // Add the edge to the minimum spanning tree
            minSpanningTree.push_back({u, parent[u - 1]});
        }
        
        for (pair<int, int> neighbor : adjacencyList[u - 1]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            int alt = distance[u - 1] + weight;
            if (alt < distance[v - 1]) {
                // Found a shorter path
                unvisited.erase({distance[v - 1], v});
                distance[v - 1] = alt;
                parent[v - 1] = u;
                unvisited.insert({distance[v - 1], v});
            }
        }
    }
    
    return minSpanningTree;
}


void WeightedGraph::clear() {
    adjacencyList.clear();
    numVertices = 0;
    numEdges = 0;
}