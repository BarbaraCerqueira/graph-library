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

SearchResult Graph::BFS(int startVertex, bool outputToFile) {
    // Mark all vertices as not visited
    vector<bool> visited(numVertices, false);

    // Create vectors to store the parent and level of each vertex
    vector<int> parent(numVertices, -1);
    vector<int> level(numVertices, -1);

    // Create a queue for BFS
    queue<int> queue;
    level[startVertex-1] = 0;
    parent[startVertex-1] = 0; // Root has no parent

    // Mark the source vertex as visited and enqueue it
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        // Dequeue a vertex from the queue and print it
        int currentVertex = queue.front();
        //cout << currentVertex << " "; // DEBUGGING
        queue.pop();

        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent vertex has not been visited, mark it
        // visited and enqueue it
        for (int adjacentVertex : findNeighbors(currentVertex)) {
            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = true;
                queue.push(adjacentVertex);
                parent[adjacentVertex-1] = currentVertex; 
                level[adjacentVertex-1] = level[currentVertex-1] + 1; 
            }
        }
    }

    if (outputToFile){
        writeTreeToFile(startVertex, parent, level, "bfs");
    }

    SearchResult result;
    result.visited = visited;
    result.parent = parent;
    result.level = level;

    return result;
}

SearchResult Graph::DFS(int startVertex, bool outputToFile) {
    // Mark all vertices as not visited
    vector<bool> visited(numVertices, false);

    // Create vectors to store the parent and level of each vertex
    vector<int> parent(numVertices, -1);
    vector<int> level(numVertices, -1);

    // Create a stack for DFS
    stack<int> stack;

    // Push the startVertex onto the stack
    stack.push(startVertex);
    level[startVertex-1] = 0;
    parent[startVertex-1] = 0; // Root has no parent

    while (!stack.empty()) {
        // Pop a vertex from the stack and mark it as visited
        int currentVertex = stack.top();
        vector<int> neighbors = findNeighbors(currentVertex);

        stack.pop();

        if (!visited[currentVertex-1]) {
            //cout << currentVertex << " "; // DEBUGGING
            visited[currentVertex-1] = true;

            // Push all unvisited adjacent vertices onto the stack
            for (int i = neighbors.size() - 1; i >= 0; --i) {
                int adjacentVertex = neighbors[i];
                if (!visited[adjacentVertex-1]) {
                    stack.push(adjacentVertex);
                    parent[adjacentVertex-1] = currentVertex; 
                    level[adjacentVertex-1] = level[currentVertex-1] + 1; 
                }
            }
        }
    }

    if (outputToFile){
        writeTreeToFile(startVertex, parent, level, "dfs");
    }

    SearchResult result;
    result.visited = visited;
    result.parent = parent;
    result.level = level;

    return result;
}

void Graph::writeTreeToFile(int startVertex, const vector<int>& parent, const vector<int>& level, string searchName) {
    // Generate a unique file name
    string fileName = searchName + "_tree.txt";
    int counter = 2;
    while (ifstream(fileName)) {
        fileName = searchName + "_tree" + to_string(counter) + ".txt";
        counter++;
    }

    // Open the file for writing
    ofstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error opening file " << fileName << endl;
        return;
    }

    // Write tree information to the file
    file << "Tree generated by " << searchName << " starting from vertex " << startVertex << ":" << endl;
    file << "---------------------------------------------" << endl;
    file << left << setw(8) << "Vertex" << setw(8) << "Parent" << setw(8) << "Level" << endl;

    for (size_t i = 0; i < parent.size(); ++i) {
        if (parent[i] == -1) {
            continue;
        } else {
            file << left << setw(8) << i + 1 << setw(8);
            
            if (parent[i] == 0) {
                file << "Root";
            } else {
                file << parent[i];
            }

            file << setw(8) << level[i] << endl;
        }
    }

    // Close the file
    file.close();
}

vector<vector<int>> Graph::findConnectedComponents() {
    vector<vector<int>> components;

    vector<bool> checked(numVertices, false);

    for (int vertex = 1; vertex <= numVertices; ++vertex) {
        if (!checked[vertex - 1]) {
            SearchResult result = DFS(vertex, false);

            // Collect vertices visited during DFS as a connected component
            vector<int> component;
            for (int i = 0; i < numVertices; ++i) {
                if (result.visited[i]) {
                    component.push_back(i + 1);
                    checked[i] = true;
                }
            }

            components.push_back(component);
        }
    }

    return components;
}

void Graph::clear(){
    numVertices = 0;
    numEdges = 0;
}