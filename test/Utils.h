#ifndef UTILS_H
#define UTILS_H

#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include "WeightedGraph.h"
#include <chrono>
#include <ctime>

using namespace std;

template<typename Function>
double wallTime (Function func) {
    auto startTime = chrono::high_resolution_clock::now();
    
    // Executes code snippet
    func();

    auto endTime = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    return static_cast<double>(duration.count()) / 1'000'000.0; // Time in seconds
}

int getRandomVertex(int numVertices) {
    // Initialize random seed with current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random number between 1 and numVertices
    int randomVertex = rand() % numVertices + 1;

    return randomVertex;
}

#endif // UTILS_H