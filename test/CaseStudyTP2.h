#ifndef CASE_STUDY_TP2_H
#define CASE_STUDY_TP2_H

#include "Utils.h"
#include <iostream>
#include <vector>
#include <string>

double dijkstraHeapTime(WeightedGraph* graph, int iterations);
double dijkstraVectorTime(WeightedGraph* graph, int iterations);

int caseStudyTP2() {
    ofstream resultsFile("case_study_tp2.csv");
    string pathGraph;

    resultsFile << unitbuf; // Activate real time file writing

    WeightedGraph* graph;

    resultsFile << "Graph,PathFrom10To20,Dist20,PathFrom10To30,Dist30,PathFrom10To40,Dist40,PathFrom10To50,"
                << "Dist50,PathFrom10To60,Dist60,DijkstraWithHeap,DijkratraWithoutHeap" << endl;

    vector<int> destinations = {20, 30, 40, 50, 60};

    // Perform case study to each graph in folder 'case-study-graphs' - All 5 must be there
    for (int test_number = 1; test_number <= 5; ++test_number) {
        // Path of file containing current graph
        pathGraph = "case-study-graphs/grafo_W_" + to_string(test_number) + ".txt";

        // Check if the file exists
        ifstream file(pathGraph);
        if (!file.good()) {
            cout << "Graph file does not exist: " << pathGraph << endl;
            continue; // Skip this iteration and move to the next graph
        }

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

            resultsFile << pathString << "," << distance << ",";
        }

        // Getting Djikstra execution time
        cout << "Finding Dijkstra average execution time using Heap..." << endl;
        resultsFile << dijkstraHeapTime(graph, 100) << ",";

        cout << "Finding Dijkstra average execution time using Vector(No Heap)..." << endl;
        if (graph->getNumEdges() < 10000000) {
            resultsFile << dijkstraVectorTime(graph, 100);
        } else {
            resultsFile << dijkstraVectorTime(graph, 1);
        }

        delete graph; // Free memory
        resultsFile << endl;
        cout << endl;
    }

    resultsFile.close();
    return 0;
}

double dijkstraHeapTime(WeightedGraph* graph, int iterations) {
    double duration, totalDuration = 0;

    for (int i = 1; i <= iterations; ++i) {
        cout << "\rIteration " << i << " of " << iterations << flush;
        int randomVertex = getRandomVertex(graph->getNumVertices());
        duration = wallTime([&graph, &randomVertex](){
            graph->dijkstraHeap(randomVertex);
        });
        totalDuration += duration;
    }
    cout << "\r" << string(50, ' ') << "\r";  // Removes progress

    double avgDuration = static_cast<double>(totalDuration) / iterations;
    return avgDuration;
}

double dijkstraVectorTime(WeightedGraph* graph, int iterations) {
    double duration, totalDuration = 0;

    for (int i = 1; i <= iterations; ++i) {
        cout << "\rIteration " << i << " of " << iterations << flush;
        int randomVertex = getRandomVertex(graph->getNumVertices());
        duration = wallTime([&graph, &randomVertex](){
            graph->dijkstraVector(randomVertex);
        });
        totalDuration += duration;
    }
    cout << "\r" << string(50, ' ') << "\r";  // Removes progress 

    double avgDuration = static_cast<double>(totalDuration) / iterations;
    return avgDuration;
}

#endif // CASE_STUDY_TP2_H