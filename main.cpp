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

    AdjacencyMatrixGraph graph; // Create graph

    graph.readGraphFromFile("case-study-graphs/teste_3.txt");
    //graph.readGraphFromFile("case-study-graphs/teste_3.txt");
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
        graph.DFS(1, false);
    });
    cout << "DFS Wall Time: " << durationInSeconds << " seconds." << endl;
    
    cout << endl; // Jump Line

    int distance;
    durationInSeconds = measureExecutionTime([&graph, &distance](){
        distance = graph.shortestDistance(1, 8);
    });
    cout << "Shortest Distance Wall Time: " << durationInSeconds << " seconds." << endl;
    cout << "Shortest Distance 1 and 8: " << distance << endl;
    cout << endl; // Jump Line

    int diameter;
    durationInSeconds = measureExecutionTime([&graph, &diameter](){
        diameter = graph.diameter();
    });
    cout << "Diameter Wall Time: " << durationInSeconds << " seconds." << endl;
    cout << "Graph diameter: " << diameter << endl;
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
    
    // Executes code snippet
    func();

    auto endTime = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    return static_cast<double>(duration.count()) / 1'000'000.0; // Time in seconds
}