#ifndef CASE_STUDY_TP3_H
#define CASE_STUDY_TP3_H

#include "Utils.h"
#include <iostream>
#include <vector>
#include <string>

double fordFulkersonTime(WeightedGraph* graph, int iterations);

int caseStudyTP3() {
    ofstream resultsFile("case_study_tp3.csv");
    string pathGraph;

    resultsFile << unitbuf; // Activate real time file writing

    WeightedGraph* graph;

    resultsFile << "Graph,MaxFlow,AverageExecTime" << endl;

    // Perform case study to each graph in folder 'case-study-graphs' - All 6 must be there
    for (int test_number = 1; test_number <= 6; ++test_number) {
        // Path of file containing current graph
        pathGraph = "case-study-graphs/grafo_rf_" + to_string(test_number) + ".txt";

        // Check if the file with the graph exists
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

        // Getting max flow from vertex 1 to 2
        cout << "Finding max flow..." << endl;
        auto result = graph->fordFulkerson(1, 2, true);
        resultsFile << result.first << ",";

        // Getting Ford Fulkerson average execution time
        cout << "Finding Ford Fulkerson average execution time..." << endl;
        resultsFile << fordFulkersonTime(graph, 10);

        delete graph; // Free memory
        resultsFile << endl;
        cout << endl;
    }

    resultsFile.close();
    return 0;
}

double fordFulkersonTime(WeightedGraph* graph, int iterations) {
    double duration, totalDuration = 0;

    for (int i = 1; i <= iterations; ++i) {
        cout << "\rIteration " << i << " of " << iterations << flush;
        int randomSource = getRandomVertex(graph->getNumVertices());
        int randomSink = getRandomVertex(graph->getNumVertices());
        duration = wallTime([&graph, &randomSource, &randomSink](){
            graph->fordFulkerson(randomSource, randomSink, false);
        });
        totalDuration += duration;
    }
    cout << "\r" << string(50, ' ') << "\r";  // Removes progress

    double avgDuration = static_cast<double>(totalDuration) / iterations;
    return avgDuration;
}

#endif // CASE_STUDY_TP3_H