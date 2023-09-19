#include "Graph.h"
#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include <vector>
#include <iostream>
#include <sys/resource.h>
#include <thread>

using namespace std;

// Testing
int main() {
    bool reading;
    int degree;

    AdjacencyListGraph graph; // Create graph

    reading = graph.readGraphFromFile("case-study-graphs/grafo_1.txt");
    if (reading){
        cout << "Leitura bem sucedida! " << endl;
    }
    else {
        cout << "Erro na leitura! " << endl;
    }

    cout << endl; // Jump Line

    degree = graph.findDegree(108);
    cout << "Grau do vertice 108: " << degree << endl;

    cout << endl; // Jump Line

    graph.showVariables();

    cout << endl; // Jump Line

    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        cout << "Memória usada pelo processo: " << usage.ru_maxrss << " KB" << endl;
    } else {
        cerr << "Erro ao obter informações de uso de recursos" << endl;
    }

    // this_thread::sleep_for(chrono::seconds(15));

    return 0;
}