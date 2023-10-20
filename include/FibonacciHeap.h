#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Represents a node of the heap
class Node {
public:
    Node(int _key, int _value);

    int key;
    int value;
    Node* child = nullptr;
    Node* parent = nullptr;
    Node* left = this;
    Node* right = this;
    bool marked = false;
    int degree = 0;
};

class FibonacciHeap {
public:
    FibonacciHeap();

    Node* insert(int key, int value);
    void decreaseKey(Node* node, int newKey);
    Node* getMin();
    Node* deleteMin();
    bool isEmpty();

private:
    Node* minNode;
    int size;

    void cut(Node* child, Node* parent);
    void cascadingCut(Node* node);
    void consolidate();
    void link(Node* child, Node* parent);
};

#endif // FIBONACCI_HEAP_H