// BinarySearchTree.cpp
#include <iostream>
#include "BinarySearchTree.h"

// Constructor / Destructor


BinarySearchTree::BinarySearchTree() : root(nullptr), m_size(0) {}

BinarySearchTree::~BinarySearchTree() {
    destroy(root);
}

// Post order traversal delete
void BinarySearchTree::destroy(Node* node) {
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

// Insert

void BinarySearchTree::Insert(const Course& course) {
    root = insert(root, course);
    ++m_size;
}

BinarySearchTree::Node* BinarySearchTree::insert(Node* node, const Course& course) {
    if (node == nullptr) {
        return new Node(course);
    }
    if (course.courseNumber < node->course.courseNumber) {
        node->left = insert(node->left, course);
    } else {
        node->right = insert(node->right, course);
    }
    return node;
}

// PrintAll

void BinarySearchTree::PrintAll() const {
    inOrder(root);
}

void BinarySearchTree::inOrder(Node* node) const {
    if (node == nullptr) return;
    inOrder(node->left);
    std::cout << node->course.courseNumber << ", "
              << node->course.courseTitle  << "\n";
    inOrder(node->right);
}

// Search

Course BinarySearchTree::Search(const std::string& courseNumber) const {
    Node* result = search(root, courseNumber);
    if (result != nullptr) {
        return result->course;
    }
    return Course{}; // courseNumber will be empty string
}

BinarySearchTree::Node* BinarySearchTree::search(Node* node,
                                                  const std::string& courseNumber) const {
    if (node == nullptr) return nullptr;
    if (node->course.courseNumber == courseNumber) return node;

    if (courseNumber < node->course.courseNumber) {
        return search(node->left, courseNumber);
    }
    return search(node->right, courseNumber);
}
