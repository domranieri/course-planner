// BinarySearchTree.h
#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <string>
#include "Course.h"

class BinarySearchTree {

private:
    struct Node {
        Course course;
        Node* left;
        Node* right;

        explicit Node(Course c) : course(c), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int   m_size; // tracks number of inserted courses

    // Recursive helpers
    Node* insert(Node* node, const Course& course);
    void  inOrder(Node* node) const;
    Node* search(Node* node, const std::string& courseNumber) const;
    void  destroy(Node* node); // post order delete for destructor

public:
    BinarySearchTree();
    ~BinarySearchTree();

    // Disable copy
    BinarySearchTree(const BinarySearchTree&)            = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    void   Insert(const Course& course);
    void   PrintAll() const;
    bool   IsEmpty() const { return root == nullptr; }
    int    Size()    const { return m_size; }

    // Returns a copy of the found course
    Course Search(const std::string& courseNumber) const;
};

#endif // BINARY_SEARCH_TREE_H_
