#include "FibonacciHeap.h"

Node::Node(int _key, int _value) {
    key = _key;
    value = _value;
}

FibonacciHeap::FibonacciHeap() {
    minNode = nullptr;
    size = 0;
}

Node* FibonacciHeap::insert(int key, int value) {
    Node* newNode = new Node(key, value);
    if (minNode == nullptr) {
        minNode = newNode;
    } else {
        minNode->left->right = newNode;
        newNode->left = minNode->left;
        minNode->left = newNode;
        newNode->right = minNode;
        if (key < minNode->key) {
            minNode = newNode;
        }
    }
    size++;
    return newNode;
}

void FibonacciHeap::decreaseKey(Node* node, int newKey) {
    if (newKey > node->key) {
        std::cerr << "New key is greater than the current key." << std::endl;
        return;
    }

    node->key = newKey;
    Node* parent = node->parent;

    if (parent != nullptr && node->key < parent->key) {
        cut(node, parent);
        cascadingCut(parent);
    }

    if (node->key < minNode->key) {
        minNode = node;
    }
}

Node* FibonacciHeap::getMin() {
    return minNode;
}

Node* FibonacciHeap::deleteMin() {
    if (minNode == nullptr) {
        return nullptr;
    }

    Node* min = minNode;
    if (minNode->child != nullptr) {
        Node* child = minNode->child;
        do {
            Node* next = child->right;
            minNode->left->right = child;
            child->right = minNode->right;
            minNode->right->left = child;
            child->left = minNode->left;
            child->parent = nullptr;
            if (child->key < minNode->key) {
                minNode = child;
            }
            child->marked = false;
            child = next;
        } while (child != minNode->child);
    }

    minNode->left->right = minNode->right;
    minNode->right->left = minNode->left;
    if (minNode == minNode->right) {
        minNode = nullptr;
    } else {
        minNode = minNode->right;
        consolidate();
    }

    size--;
    return min;
}

bool FibonacciHeap::isEmpty() {
    return size == 0;
}

void FibonacciHeap::cut(Node* child, Node* parent) {
    child->left->right = child->right;
    child->right->left = child->left;
    parent->child = child->right;
    parent->degree--;

    child->left = minNode;
    child->right = minNode->right;
    minNode->right->left = child;
    minNode->right = child;

    child->parent = nullptr;
    child->marked = false;
}

void FibonacciHeap::cascadingCut(Node* node) {
    Node* parent = node->parent;
    if (parent != nullptr) {
        if (!node->marked) {
            node->marked = true;
        } else {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

void FibonacciHeap::consolidate() {
    int maxDegree = static_cast<int>(log(size) / log(1.618)); // Golden ratio

    std::vector<Node*> degreeTable(maxDegree + 1, nullptr);
    Node* nodesToVisit = minNode;
    std::vector<Node*> nodes;

    do {
        nodes.push_back(nodesToVisit);
        nodesToVisit = nodesToVisit->right;
    } while (nodesToVisit != minNode);

    for (Node* node : nodes) {
        int degree = node->degree;
        while (degreeTable[degree] != nullptr) {
            Node* other = degreeTable[degree];
            if (node->key > other->key) {
                std::swap(node, other);
            }
            link(other, node);
            degreeTable[degree] = nullptr;
            degree++;
        }
        degreeTable[degree] = node;
    }

    minNode = nullptr;
    for (int i = 0; i <= maxDegree; i++) {
        if (degreeTable[i] != nullptr) {
            if (minNode == nullptr) {
                minNode = degreeTable[i];
            } else {
                degreeTable[i]->left->right = degreeTable[i]->right;
                degreeTable[i]->right->left = degreeTable[i]->left;
                degreeTable[i]->left = minNode;
                degreeTable[i]->right = minNode->right;
                minNode->right->left = degreeTable[i];
                minNode->right = degreeTable[i];
                if (degreeTable[i]->key < minNode->key) {
                    minNode = degreeTable[i];
                }
            }
        }
    }
}

void FibonacciHeap::link(Node* child, Node* parent) {
    child->left->right = child->right;
    child->right->left = child->left;

    child->parent = parent;
    if (parent->child == nullptr) {
        parent->child = child;
        child->right = child;
        child->left = child;
    } else {
        child->left = parent->child;
        child->right = parent->child->right;
        parent->child->right->left = child;
        parent->child->right = child;
    }

    parent->degree++;
    child->marked = false;
}