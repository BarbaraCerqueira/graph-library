#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include <vector>
#include <iostream>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename Function>
double wallTime(Function func);
void getMemoryUsage();
int userInteraction();
int caseStudy();
double BFSAvgExecutionTime(Graph* graph);
double DFSAvgExecutionTime(Graph* graph);
int getVertexParentBFS(Graph* graph, int startVertex, int childVertex);
int getVertexParentDFS(Graph* graph, int startVertex, int childVertex);
int getRandomVertex(int numVertices);
size_t estimateMatrixMemoryUsage(string filepath);
size_t getTotalMemory();

int main() {
    
    int choice;

    cout << endl << "Graph Library Testing Interface" << endl;
    cout << "-------------------------------" << endl;

    cout << endl << "Choose mode:" << endl;
    cout << "1. User Interaction" << endl;
    cout << "2. Run Case Study" << endl;
    cin >> choice;

    if (choice == 1) {
        userInteraction();
    } else if (choice == 2) {
        caseStudy();
    } else {
        cout << "Invalid choice." << endl;
        return 1;
    }

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

int userInteraction() {
    int choice;
    double duration;
    Graph* graph;

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
    ofstream resultsFile("case_study.csv");
    string pathGraph;

    resultsFile << unitbuf; // Activate real time file writing

    Graph* graph;

    resultsFile << "Graph,MatrixExecTimeBFS,MatrixExecTimeDFS,ListExecTimeBFS,ListExecTimeDFS,Parent10fromBFS,"
                << "Parent20fromBFS,Parent30fromBFS,Parent10fromDFS,Parent20fromDFS,Parent30fromDFS,"
                << "NumConnectedComponents,BiggestComponent,SmallestComponent,Diameter" << endl;

    // Perform case study to each graph in folder 'case-study-graphs' - All 6 must be there
    for (int test_number = 1; test_number <= 6; ++test_number) {

        // Path of file containing current graph
        pathGraph = "case-study-graphs/grafo_" + to_string(test_number) + ".txt";

        cout << "Running tests on Graph " << test_number << "..." << endl;
        resultsFile << test_number << ",";

        cout << "Getting BFS and DFS average execution for Adjacency Matrix..." << endl;

        if (estimateMatrixMemoryUsage(pathGraph) < getTotalMemory()){
            // Initialize graph as Adjacency Matrix
            graph = new AdjacencyMatrixGraph();
            graph->readGraphFromFile(pathGraph);

            // Get average BFS and DFS execution time for Matrix
            resultsFile << BFSAvgExecutionTime(graph) << "," << DFSAvgExecutionTime(graph) << ",";

            // Free memory
            delete graph;
        }
        // Not safe to proceed with memory allocation - graph too large
        else { 
            // Exception due to excess memory allocation
            resultsFile << "Memory excess" << "Memory excess" << ",";
            cout << "Not possible to allocate Adjacency Matrix!" << endl;
        }
            
        cout << "Getting BFS and DFS average execution for Adjacency List..." << endl;

        // Initialize graph as Adjacency List
        graph = new AdjacencyListGraph();
        graph->readGraphFromFile(pathGraph);

        // Get average BFS and DFS execution time for List
        resultsFile << BFSAvgExecutionTime(graph) << "," << DFSAvgExecutionTime(graph) << ",";

        cout << "Searching for parents..." << endl;

        // Get parents of vertices 10, 20, 30 through BFS and DFS
        resultsFile << getVertexParentBFS(graph, 1, 10) << "," << getVertexParentBFS(graph, 2, 20) << "," << getVertexParentBFS(graph, 3, 30) << ",";
        resultsFile << getVertexParentDFS(graph, 1, 10) << "," << getVertexParentDFS(graph, 2, 20) << "," << getVertexParentDFS(graph, 3, 30) << ",";

        cout << "Finding connected components..." << endl;

        // Get connected components information
        vector<vector<int>> components = graph->findConnectedComponents();
        resultsFile << components.size() << "," << components.front().size() << "," << components.back().size() << ",";

        cout << "Finding graph diameter..." << endl;

        // Get diameter
        resultsFile << graph->diameter() << endl;

        // Free memory
        delete graph;

        cout << endl;
    }

    resultsFile.close();

    return 0;
}

double BFSAvgExecutionTime(Graph* graph) {
    double duration, totalDuration = 0;

    for (int i = 1; i <= 100; ++i) {
        int randomVertex = getRandomVertex(graph->getNumVertices());
        duration = wallTime([&graph, &randomVertex](){
            graph->BFS(randomVertex, false);
        });
        totalDuration += duration;
    }

    return totalDuration / 100.0;
}

double DFSAvgExecutionTime(Graph* graph) {
    double duration, totalDuration = 0;

    for (int i = 1; i <= 100; ++i) {
        int randomVertex = getRandomVertex(graph->getNumVertices());
        duration = wallTime([&graph, &randomVertex](){
            graph->DFS(randomVertex, false);
        });
        totalDuration += duration;
    }

    return totalDuration / 100.0;
}

int getVertexParentBFS(Graph* graph, int startVertex, int childVertex) {
    SearchResult result;
    result = graph->BFS(startVertex, false);
    return result.parent[childVertex-1];
}

int getVertexParentDFS(Graph* graph, int startVertex, int childVertex) {
    SearchResult result;
    result = graph->DFS(startVertex, false);
    return result.parent[childVertex-1];
}

int getRandomVertex(int numVertices) {
    // Initialize random seed with current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random number between 1 and numVertices
    int randomVertex = rand() % numVertices + 1;

    return randomVertex;
}

// Estimates size of Adjacency Matrix in bytes
size_t estimateMatrixMemoryUsage(string filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        return -1; // Error trying to open file
    }

    // Reads number of vertices
    int numVertices;
    file >> numVertices;

    size_t totalElements = static_cast<size_t>(numVertices) * numVertices;
    size_t estimateMemory = totalElements * sizeof(bool);

    file.close();

    return estimateMemory;
}

// Gets amount of available memory in system
size_t getTotalMemory() {
    struct sysinfo info;

    if (sysinfo(&info) != 0) {
        cerr << "Error getting system information" << endl;
        return -1;
    }

    size_t totalMemory = info.totalram * info.mem_unit;

    return totalMemory;
}