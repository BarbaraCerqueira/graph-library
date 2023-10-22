#include "FibonacciHeap.h"

FibonacciHeap::FibonacciHeap() {
}

bool FibonacciHeap::isEmpty() {
    return minNode == nullptr;
}

Node* FibonacciHeap::insert(float key, int value) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = value;
    newNode->degree = 0;
    newNode->marked = false;
    newNode->parent = nullptr;
    newNode->child = nullptr;
    if (minNode == nullptr) {
        newNode->left = newNode;
        newNode->right = newNode;
        minNode = newNode;
    } else {
        newNode->left = minNode;
        newNode->right = minNode->right;
        minNode->right = newNode;
        newNode->right->left = newNode;
        if (key < minNode->key) {
            minNode = newNode;
        }
    }
    numNodes++;
    return newNode;
}

Node* FibonacciHeap::getMin() {
    return minNode;
}

Node* FibonacciHeap::extractMin() {
    Node* z = minNode;
    if (z != nullptr) {
        Node* child = z->child;
        if (child != nullptr) {
            Node* c = child;
            do {
                Node* next = c->right;
                c->left = z;
                c->right = z->right;
                z->right = c;
                c->right->left = c;
                c->parent = nullptr;
                c = next;
            } while (c != child);
        }
        z->left->right = z->right;
        z->right->left = z->left;
        if (z == z->right) {
            minNode = nullptr;
        } else {
            minNode = z->right;
            consolidate();
        }
        numNodes--;
    }
    return z;
}

void FibonacciHeap::decreaseKey(Node* node, float newKey) {
    if (newKey > node->key) {
        cerr << "New key is greater than the current key." << endl;
        return;
    }
    node->key = newKey;
    Node* y = node->parent;
    if (y != nullptr && node->key < y->key) {
        cut(node, y);
        cascadingCut(y);
    }
    if (node->key < minNode->key) {
        minNode = node;
    }
}

void FibonacciHeap::link(Node* y, Node* x) {
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (x->child == nullptr) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right = y;
        y->right->left = y;
    }
    x->degree++;
    y->marked = false;
}

void FibonacciHeap::consolidate() {
    int maxDegree = static_cast<int>(log2(numNodes)) + 1;

    Node* nodes[maxDegree+1];
    for (int i = 0; i < maxDegree+1; i++) {
        nodes[i] = nullptr;
    }

    Node* x = minNode;
    int numRoots = 0;
    Node* next;
    do {
        numRoots++;
        x = x->right;
    } while (x != minNode);

    while (numRoots > 0) {
        int d = x->degree;
        next = x->right;
        while (nodes[d] != nullptr) {
            Node* y = nodes[d];
            if (x->key > y->key) {
                Node* temp = x;
                x = y;
                y = temp;
            }
            link(y, x);
            nodes[d] = nullptr;
            d++;
        }
        nodes[d] = x;
        x = next;
        numRoots--;
    }

    minNode = nullptr;
    for (int i = 0; i < maxDegree; i++) {
        if (nodes[i] != nullptr) {
            if (minNode == nullptr) {
                minNode = nodes[i];
            } else {
                if (nodes[i]->key < minNode->key) {
                    minNode = nodes[i];
                }
            }
        }
    }
}

void FibonacciHeap::cut(Node* x, Node* y) {
    x->left->right = x->right;
    x->right->left = x->left;
    y->degree--;
    if (y->child == x) {
        y->child = x->right;
    }
    if (y->degree == 0) {
        y->child = nullptr;
    }
    x->left = minNode;
    x->right = minNode->right;
    minNode->right = x;
    x->right->left = x;
    x->parent = nullptr;
    x->marked = false;
}

void FibonacciHeap::cascadingCut(Node* y) {
    Node* z = y->parent;
    if (z != nullptr) {
        if (!y->marked) {
            y->marked = true;
        } else {
            cut(y, z);
            cascadingCut(z);
        }
    }
}