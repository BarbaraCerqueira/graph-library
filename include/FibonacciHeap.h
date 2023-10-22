#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <vector>
#include <limits>
#include <cmath>
#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
    float key;
    int value;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool marked;
    int degree;
};

class FibonacciHeap {
    public:
        FibonacciHeap();

        bool isEmpty();
        Node* insert(float key, int value);
        Node* getMin();
        Node* extractMin();
        void decreaseKey(Node* node, float newKey);

    private:
        Node* minNode = nullptr;
        int numNodes = 0;

        void link(Node* y, Node* x);
        void consolidate();
        void cut(Node* x, Node* y);
        void cascadingCut(Node* y);
};

#endif // FIBONACCI_HEAP_H
