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
double wallTime(Function func);
void getMemoryUsage();
int userInteraction(Graph* graph);
int caseStudy(Graph* graph);

int main() {

    // AdjacencyMatrixGraph graph; // Create graph

    // graph.readGraphFromFile("case-study-graphs/teste_3.txt");
    // cout << endl; // Jump Line

    // // Pause execution to stabilize memory usage
    // this_thread::sleep_for(chrono::seconds(5));
    // struct rusage usage;
    // if (getrusage(RUSAGE_SELF, &usage) == 0) {
    //     cout << "Memória usada pelo processo: " << usage.ru_maxrss << " KB" << endl;
    // } else {
    //     cerr << "Erro ao obter informações de uso de recursos." << endl;
    // }
    // cout << endl; // Jump Line

    // int diameter;
    // double durationInSeconds = wallTime([&graph, &diameter](){
    //     diameter = graph.diameter();
    // });
    // cout << "Diameter Wall Time: " << durationInSeconds << " seconds." << endl;
    // cout << "Graph diameter: " << diameter << endl;
    // cout << endl; // Jump Line
    
    int choice;
    Graph* graph = nullptr;;

    cout << endl << "Graph Library Testing Interface" << endl;
    cout << "-------------------------------" << endl;

    cout << endl << "Choose mode:" << endl;
    cout << "1. User Interaction" << endl;
    cout << "2. Run Case Study" << endl;
    cin >> choice;

    if (choice == 1) {
        userInteraction(graph);
    } else if (choice == 2) {
        return 0; // building
    } else {
        cout << "Invalid choice." << endl;
        return 1;
    }

    //delete graph;

    return 0;
}

template<typename Function>
double wallTime (Function func) {
    auto startTime = chrono::high_resolution_clock::now();
    
    // Executes code snippet
    func();

    auto endTime = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    return static_cast<double>(duration.count()) / 1'000'000.0; // Time in seconds
}

void getMemoryUsage() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        cout << "Memory used by the process: " << static_cast<double>(usage.ru_maxrss) / 1024.0 << " MB" << endl;
    } else {
        cerr << "Error getting resource usage information." << endl;
    }
}

int userInteraction(Graph* graph) {
    int choice;
    double duration;

    cout << endl << "Choose the graph representation:" << endl;
    cout << "1. Adjacency Matrix" << endl;
    cout << "2. Adjacency List" << endl;
    cin >> choice;

    if (choice == 1) {
        graph = new AdjacencyMatrixGraph();
    } else if (choice == 2) {
        graph = new AdjacencyListGraph();
    } else {
        cout << "Invalid choice." << endl;
        return 1;
    }

    string filepath;
    cout << endl << "Enter the path to the graph file: ";
    cin >> filepath;

    if (!graph->readGraphFromFile(filepath)) {
        cout << "Error reading the graph file." << endl;
        delete graph;
        return 1;
    }

    while (true) {
        cout << endl << "Choose an operation:" << endl;
        cout << "1. BFS" << endl;
        cout << "2. DFS" << endl;
        cout << "3. Find Connected Components" << endl;
        cout << "4. Shortest Distance" << endl;
        cout << "5. Diameter" << endl;
        cout << "6. Generate Graph Info File" << endl;
        cout << "7. Check Memory Usage" << endl;
        cout << "8. Quit" << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                int startVertex;
                cout << "Enter the starting vertex: ";
                cin >> startVertex;
                duration = wallTime([&graph, &startVertex](){
                    graph->BFS(startVertex);
                });
                cout << "BFS execution finished after " << duration << " seconds." << endl;
                cout << "Spanning tree information file was generated." << endl;
                break;
            }
            case 2: {
                int startVertex;
                cout << "Enter the starting vertex: ";
                cin >> startVertex;
                duration = wallTime([&graph, &startVertex](){
                    graph->DFS(startVertex);
                });
                cout << "DFS execution finished after " << duration << " seconds." << endl;
                cout << "Spanning tree information file was generated." << endl;
                break;
            }
            case 3: {
                vector<vector<int>> components = graph->findConnectedComponents();
                cout << "The graph has a total of " << components.size() << " connected component(s)." << endl;
                cout << "Biggest component: " << components.front().size() << " vertices" << endl;
                cout << "Smallest component: " << components.back().size() << " vertices" << endl;
                break;
            }
            case 4: {
                int source, destination;
                cout << "Enter source and destination vertices: ";
                cin >> source >> destination;
                int distance = graph->shortestDistance(source, destination);
                if (distance == -1) {
                    cout << "No path exists between source and destination." << endl;
                } else {
                    cout << "Shortest distance: " << distance << endl;
                }
                break;
            }
            case 5: {
                int diameter;
                duration = wallTime([&graph, &diameter](){
                    diameter = graph->diameter();
                });
                cout << "Diameter search finished after " << duration << " seconds." << endl;
                cout << "Diameter: " << diameter << endl;
                break;
            }
            case 6: {
                graph->generateGraphInfoFile();
                cout << "Graph information file generated." << endl;
                break;
            }
            case 7: {
                getMemoryUsage();
                break;
            }
            case 8: {
                cout << "Execution terminated." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice." << endl;
            }
        }
    }

    return 0;
} 

int caseStudy(Graph* graph) {

    ofstream resultsFile("case_study.txt");
}