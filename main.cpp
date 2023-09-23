#include "Graph.h"
#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include <vector>
#include <iostream>
#include <sys/resource.h>
#include <thread>
#include <chrono>

using namespace std;

template<typename Function>
double measureExecutionTime(Function func);


int main() {

    AdjacencyListGraph graph; // Create graph

    graph.readGraphFromFile("case-study-graphs/grafo_2.txt");
    cout << endl; // Jump Line

    // Pause execution to stabilize memory usage
    this_thread::sleep_for(chrono::seconds(5));
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        cout << "Memória usada pelo processo: " << usage.ru_maxrss << " KB" << endl;
    } else {
        cerr << "Erro ao obter informações de uso de recursos." << endl;
    }

    cout << endl; // Jump Line

    double durationInSeconds = measureExecutionTime([&graph](){
        graph.DFS(1);
    });
    cout << "DFS Wall Time: " << durationInSeconds << " seconds." << endl;
    
    cout << endl; // Jump Line

    vector<vector<int>> connectedComponents = graph.findConnectedComponents();
    cout << "Graph has " << connectedComponents.size() << " connected component(s)." << endl; 
    // Print the connected components' size
    int counter = 1;
    for (const vector<int>& component : connectedComponents) {
        cout << "Connected Component " << counter << ": " << component.size() << " vertices." << endl;
        counter++;
    }
    
    return 0;
}


template<typename Function>
double measureExecutionTime(Function func) {
    auto startTime = chrono::high_resolution_clock::now();
    
    // Execute o trecho de código que você deseja medir
    func();

    auto endTime = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    return static_cast<double>(duration.count()) / 1'000'000.0; // Time in seconds
}