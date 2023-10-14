#ifndef CASE_STUDY_TP1_H
#define CASE_STUDY_TP1_H

#include "Utils.h"
#include <iostream>
#include <sys/sysinfo.h>

double BFSAvgExecutionTime(UnweightedGraph* graph);
double DFSAvgExecutionTime(UnweightedGraph* graph);
int getVertexParentBFS(UnweightedGraph* graph, int startVertex, int childVertex);
int getVertexParentDFS(UnweightedGraph* graph, int startVertex, int childVertex);
size_t estimateMatrixMemoryUsage(string filepath);
size_t getTotalMemory();

int caseStudyTP1() {
    ofstream resultsFile("case_study_tp1.csv");
    string pathGraph;

    resultsFile << unitbuf; // Activate real time file writing

    UnweightedGraph* graph;

    resultsFile << "Graph,MatrixExecTimeBFS,MatrixExecTimeDFS,ListExecTimeBFS,ListExecTimeDFS,Parent10fromBFS,"
                << "Parent20fromBFS,Parent30fromBFS,Parent10fromDFS,Parent20fromDFS,Parent30fromDFS,"
                << "Dist10to20,Dist10to30,Dist20to30,NumConnectedComponents,BiggestComponent,SmallestComponent,Diameter" << endl;

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
            resultsFile << "Memory excess," << "Memory excess,";
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

        cout << "Searching for minimum distances..." << endl;

        // Get distance from vertices 10 to 20, 10 to 30 and 20 to 30
        resultsFile << graph->shortestDistance(10,20) << "," << graph->shortestDistance(10,30) << "," << graph->shortestDistance(20,30) << ",";

        cout << "Finding connected components..." << endl;

        // Get connected components information
        vector<vector<int>> components = graph->findConnectedComponents();
        resultsFile << components.size() << "," << components.front().size() << "," << components.back().size() << ",";

        cout << "Finding graph diameter..." << endl;

        // Get diameter
        if (graph->getNumVertices() < 500000) {
            resultsFile << graph->diameter() << endl;
        }
        // Graph is too large, process will take too long -> just estimate diameter
        else {           
            cout << "Graph is too large, diameter to be found next is just an estimate!" << endl;
            resultsFile << graph->estimateDiameter() << endl;
        }

        // Free memory
        delete graph;

        cout << endl;
    }

    resultsFile.close();

    return 0;
}

double BFSAvgExecutionTime(UnweightedGraph* graph) {
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

double DFSAvgExecutionTime(UnweightedGraph* graph) {
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

int getVertexParentBFS(UnweightedGraph* graph, int startVertex, int childVertex) {
    SearchResult result;
    result = graph->BFS(startVertex, false);
    return result.parent[childVertex-1];
}

int getVertexParentDFS(UnweightedGraph* graph, int startVertex, int childVertex) {
    SearchResult result;
    result = graph->DFS(startVertex, false);
    return result.parent[childVertex-1];
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

#endif // CASE_STUDY_TP1_H