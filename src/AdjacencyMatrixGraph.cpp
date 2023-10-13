#include "AdjacencyMatrixGraph.h"


AdjacencyMatrixGraph::AdjacencyMatrixGraph() : UnweightedGraph() {
}

void AdjacencyMatrixGraph::setGraphSize(int _numVertices) {
    matrix.resize(_numVertices);
    for (int i = 0; i < _numVertices; i++) {
        matrix[i].resize(_numVertices, false);
    }
}

void AdjacencyMatrixGraph::addEdge(int source, int destination) {
    if (source > 0 && source <= numVertices && destination > 0 && destination <= numVertices) {
        matrix[source-1][destination-1] = true;
        matrix[destination-1][source-1] = true;
    } else {
        cout << "Invalid vertices!" << endl;
    }
}

void AdjacencyMatrixGraph::addVertex() {
    numVertices++;
    // Add a new row and a new column with zeros to the matrix
    matrix.push_back(vector<bool>(numVertices, false));
    for (int i = 0; i < numVertices - 1; i++) {
        matrix[i].push_back(false);
    }
}

vector<int> AdjacencyMatrixGraph::findNeighbors(int vertex) {
    vector<int> neighbors;
    if (vertex > 0 && vertex <= numVertices) {
        for (int i = 0; i < numVertices; i++) {
            if (matrix[vertex-1][i] == 1) {
                neighbors.push_back(i+1);
            }
        }
    } else {
        cout << "Invalid vertex!" << endl;
    }
    return neighbors;
}

int AdjacencyMatrixGraph::findDegree(int vertex) {
    if (vertex > 0 && vertex <= numVertices) {
        int degree = 0;
        for (int i = 0; i < numVertices; i++) {
            if (matrix[vertex-1][i] == 1) {
                degree++;
            }
        }
        return degree;
    } else {
        cout << "Invalid vertex!" << endl;
        return -1;
    }
}

void AdjacencyMatrixGraph::clear(){
    matrix.clear();
    UnweightedGraph::clear();
}

