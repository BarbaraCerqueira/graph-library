#include "Graph.h"

using namespace std;

Graph::Graph() {
    numVertices = 0;
    numEdges = 0;
}

bool Graph::readGraphFromFile(string filepath) {
    clear();

    ifstream file(filepath);
    if (!file.is_open()) {
        return false; // Error trying to open file
    }

    // Reads number of vertices
    file >> numVertices;

    // Builds graph structure
    setGraphSize(numVertices);

    // Reads edges
    int source, destination;
    while (file >> source >> destination) {
        addEdge(source, destination);
        numEdges++;
    }

    file.close();
    return true; // Graph read succesfully
}


void Graph::showVariables(){
    cout << "Numero de vertices: " << numVertices << endl;
    cout << "Numero de arestas: " << numEdges << endl;
}

void Graph::BFS(int startVertex) {
    // Mark all vertices as not visited
    std::vector<bool> visited(numVertices, false);

    // Create a queue for BFS
    std::queue<int> queue;

    // Mark the source vertex as visited and enqueue it
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        // Dequeue a vertex from the queue and print it
        int currentVertex = queue.front();
        std::cout << currentVertex << " ";
        queue.pop();

        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent vertex has not been visited, mark it
        // visited and enqueue it
        for (int adjacentVertex : findNeighbors(currentVertex)) {
            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = true;
                queue.push(adjacentVertex);
            }
        }
    }
}

void Graph::DFS(int startVertex) {
        // Mark all vertices as not visited
        std::vector<bool> visited(numVertices, false);

        // Create a stack for DFS
        std::stack<int> stack;

        // Push the startVertex onto the stack
        stack.push(startVertex);

        while (!stack.empty()) {
            // Pop a vertex from the stack and mark it as visited
            int currentVertex = stack.top();
            vector<int> neighbors = findNeighbors(currentVertex);

            stack.pop();

            if (!visited[currentVertex]) {
                std::cout << currentVertex << " ";
                visited[currentVertex] = true;
            }

            // Push all unvisited adjacent vertices onto the stack
            for (int i = neighbors.size() - 1; i >= 0; --i) {
                int adjacentVertex = neighbors[i];
                if (!visited[adjacentVertex]) {
                    stack.push(adjacentVertex);
                }
            }
        }
    }

void Graph::clear(){
    numVertices = 0;
    numEdges = 0;
}