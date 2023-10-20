#include "CaseStudyTP1.h"
#include "CaseStudyTP2.h"

#include <vector>
#include <iostream>
#include <sys/resource.h>
#include <cstdlib>

using namespace std;

void getMemoryUsage();
int userInteraction();
int caseStudy();
int WeightedGraphInteraction();
int UnweightedGraphInteraction();

int main() {

    WeightedGraph* graph = new WeightedGraph();
    graph->readGraphFromFile("case-study-graphs/teste_2.txt");
    int n = graph->findDegree(6);
    cout << "Grau do vertice 6: " << n << endl;
    pair<int, list<int>> pathInfo;
    DijkstraResult result = graph->dijkstraVector(1);

    pathInfo = graph->shortestPath(1,8);
    cout << "Path between 1 and 4, distance is " << pathInfo.first << " and path is ";
    for (int vertex : pathInfo.second) {
        cout << vertex << "-";
    }
    cout << endl;
    delete graph;
    
    // int choice;

    // cout << endl << "Graph Library Testing Interface" << endl;
    // cout << "-------------------------------" << endl;

    // cout << endl << "Choose mode:" << endl;
    // cout << "1. User Interaction" << endl;
    // cout << "2. Run Case Study" << endl;
    // cin >> choice;

    // if (choice == 1) {
    //     userInteraction();
    // } else if (choice == 2) {
    //     caseStudy();
    // } else {
    //     cout << "Invalid choice." << endl;
    //     return 1;
    // }

    return 0;
}

int userInteraction() {
    int choice;

    cout << endl << "Choose the type of graph:" << endl;
    cout << "1. Weighted Graph" << endl;
    cout << "2. Unweighted Graph" << endl;
    cin >> choice;

    if (choice == 1) {;
        WeightedGraphInteraction();
    } else if (choice == 2) {
        UnweightedGraphInteraction();
    } else {
        cout << "Invalid choice." << endl;
        return 1;
    }

    return 0;
} 

int WeightedGraphInteraction() {
    WeightedGraph* graph = new WeightedGraph();

    string filepath;
    cout << endl << "Enter the path to the graph file: ";
    cin >> filepath;

    if (!graph->readGraphFromFile(filepath)) {
        cout << "Error reading the graph file." << endl;
        delete graph;
    }

    int choice;
    while (true) {
        cout << endl << "Choose an operation:" << endl;
        cout << "1. Check Memory Usage" << endl;
        cout << "2. Quit" << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                getMemoryUsage();
                break;
            }
            case 2: {
                delete graph;
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

int UnweightedGraphInteraction() {
    UnweightedGraph* graph;
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
                delete graph;
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

int caseStudy() {
    int choice;

    cout << endl << "Choose which test set to run:" << endl;
    cout << "1. Trabalho Pratico 1 (TP1)" << endl;
    cout << "2. Trabalho Pratico 2 (TP2)" << endl;
    cin >> choice;

    if (choice == 1) {
        caseStudyTP1();
    } else if (choice == 2) {
        caseStudyTP2();
    } else {
        cout << "Invalid choice." << endl;
        return 1;
    }

    return 0;
}

void getMemoryUsage() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        cout << "Memory used by the process: " << static_cast<double>(usage.ru_maxrss) / 1024.0 << " MB" << endl;
    } else {
        cerr << "Error getting resource usage information." << endl;
    }
}
