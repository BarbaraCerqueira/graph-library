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
        if (z->child != nullptr) {
            Node* child = z->child;
            Node* temp = child;
            do {
                Node* nextChild = temp->right;
                minNode->left->right = temp;
                temp->right = minNode;
                temp->left = minNode->left;
                minNode->left = temp;
                if (temp->key < minNode->key) {
                    minNode = temp;
                }
                temp->parent = nullptr;
                temp = nextChild;
            } while (temp != child);
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
    vector<Node*> degreeTable(maxDegree+1, nullptr);

    Node* current = minNode;
    vector<Node*> nodes;
    while (true) {
        nodes.push_back(current);
        current = current->right;
        if (current == minNode) {
            break;
        }
    }

    for (Node* node : nodes) {
        Node* x = node;
        int degree = x->degree;
        while (degreeTable[degree] != nullptr) {
            Node* y = degreeTable[degree];
            if (x->key > y->key) {
                swap(x, y);
            }
            link(y, x);
            degreeTable[degree] = nullptr;
            degree++;
        }
        degreeTable[degree] = x;
    }

    minNode = nullptr;
    for (Node* node : degreeTable) {
        if (node != nullptr) {
            if (minNode == nullptr) {
                minNode = node;
            } else {
                if (node->key < minNode->key) {
                    minNode = node;
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