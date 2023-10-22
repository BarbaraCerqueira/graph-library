#ifndef CASE_STUDY_TP2_H
#define CASE_STUDY_TP2_H

#include "Utils.h"
#include <iostream>
#include <vector>
#include <string>

double dijkstraHeapTime(WeightedGraph* graph);
double dijkstraVectorTime(WeightedGraph* graph);

int caseStudyTP2() {
    ofstream resultsFile("case_study_tp2.csv");
    string pathGraph;

    resultsFile << unitbuf; // Activate real time file writing

    WeightedGraph* graph;

    resultsFile << "Graph,PathFrom10To20,Dist20,PathFrom10To30,Dist30,PathFrom10To40,Dist40,PathFrom10To50,"
                << "Dist50,PathFrom10To60,Dist60,DijkstraWithHeap,DijkratraWithoutHeap" << endl;

    vector<int> destinations = {20, 30, 40, 50, 60};

    // Perform case study to each graph in folder 'case-study-graphs' - All 5 must be there
    for (int test_number = 1; test_number <= 6; ++test_number) {
        // Path of file containing current graph
        pathGraph = "case-study-graphs/grafo_W_" + to_string(test_number) + ".txt";

        // Initialize graph
        graph = new WeightedGraph();
        graph->readGraphFromFile(pathGraph);

        cout << "Running tests on Graph " << test_number << "..." << endl;
        resultsFile << test_number << ",";

        // Getting shortest path and distances from 10 to 20,30,40,50 and 60
        for (int destination : destinations){
            cout << "Finding Shortest Path from 10 to " << destination << "..." << endl;

            pair<float, list<int>> pathSearch = graph->shortestPath(10, destination, true);
            float distance = pathSearch.first;
            list<int> path = pathSearch.second;

            string pathString;
            for (auto it = path.begin(); it != path.end(); ++it) {
                pathString += to_string(*it);
                pathString += (next(it) != path.end()) ? "-" : "";
            }

            resultsFile << pathString << distance;
        }

        // Getting Djikstra execution time
        cout << "Finding Dijkstra average execution time using Heap..." << endl;
        resultsFile << dijkstraHeapTime(graph);
        cout << "Finding Dijkstra average execution time using Vector(No Heap)..." << endl;
        resultsFile << dijkstraVectorTime(graph);

        delete graph; // Free memory
        resultsFile << endl;
        cout << endl;
    }

    resultsFile.close();
    return 0;
}

double dijkstraHeapTime(WeightedGraph* graph) {
    double duration, totalDuration = 0;

    for (int i = 1; i <= 100; ++i) {
        int randomVertex = getRandomVertex(graph->getNumVertices());
        duration = wallTime([&graph, &randomVertex](){
            graph->dijkstraHeap(randomVertex);
        });
        totalDuration += duration;
    }

    return totalDuration / 100.0;
}

double dijkstraVectorTime(WeightedGraph* graph) {
    double duration, totalDuration = 0;

    for (int i = 1; i <= 100; ++i) {
        int randomVertex = getRandomVertex(graph->getNumVertices());
        duration = wallTime([&graph, &randomVertex](){
            graph->dijkstraVector(randomVertex);
        });
        totalDuration += duration;
    }

    return totalDuration / 100.0;
}

#endif // CASE_STUDY_TP2_H