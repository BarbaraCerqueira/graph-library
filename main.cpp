#include "Graph.h"
#include "AdjacencyMatrixGraph.h"
#include <vector>
#include <iostream>

using namespace std;

// Testing
int main() {
    bool reading;
    int degree;

    AdjacencyMatrixGraph graph; // Create graph
    reading = graph.readGraphFromFile("case-study-graphs/grafo_1.txt");
    if (reading){
        cout << "Leitura bem sucedida! " << endl;
    }
    else {
        cout << "Erro na leitura! " << endl;
    }

    cout << endl;

    degree = graph.findDegree(1);
    cout << "Grau do vertice 1: " << degree << endl;

    
    /*graph.setGraphSize(5);

    // Add some edges
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);

    // Find the neighbors of vertex 1
    vector<int> neighbors = graph.findNeighbors(1);
    cout << "Neighbors of vertex 1: ";
    for (int neighbor : neighbors) {
        cout << neighbor << " ";
    }
    cout << endl;

    // Discover the degree of vertex 1
    int degree = graph.findDegree(2);
    cout << "Degree of vertex 2: " << degree << endl;*/

    return 0;
}