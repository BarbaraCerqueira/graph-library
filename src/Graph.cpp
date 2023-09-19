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

void Graph::clear(){
    numVertices = 0;
    numEdges = 0;
}



