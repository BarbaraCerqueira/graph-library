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
    bool reading1;
    bool reading2;
    int degree;

    AdjacencyListGraph graph1; // Create graph
    AdjacencyListGraph graph2; // Create graph

    reading1 = graph1.readGraphFromFile("case-study-graphs/teste_1.txt");
    reading2 = graph2.readGraphFromFile("case-study-graphs/teste_2.txt");
    if (reading1 && reading2){
        cout << "Leitura bem sucedida! " << endl;
    }
    else {
        cout << "Erro na leitura! " << endl;
    }

    cout << endl; // Jump Line

    degree = graph2.findDegree(4);
    cout << "Grau do vertice 4: " << degree << endl;

    cout << endl; // Jump Line

    graph1.showVariables();

    cout << endl; // Jump Line

    graph1.BFS(5);

    cout << endl; // Jump Line

    graph2.DFS(4);

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