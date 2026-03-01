// CS300 - Project Two
// Dominic Ranieri

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// Course Structure

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};


// Binary Search Tree

class BinarySearchTree {

private:
    struct Node {
        Course course;
        Node* left;
        Node* right;

        Node(Course c) {
            course = c;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    // Insert helper
    Node* insert(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);
        }

        if (course.courseNumber < node->course.courseNumber) {
            node->left = insert(node->left, course);
        }
        else {
            node->right = insert(node->right, course);
        }

        return node;
    }

    // In order traversal helper
    void inOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }

        inOrder(node->left);
        cout << node->course.courseNumber << ", "
            << node->course.courseTitle << endl;
        inOrder(node->right);
    }

    // Search helper
    Node* search(Node* node, string courseNumber) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->course.courseNumber == courseNumber) {
            return node;
        }

        if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }

        return search(node->right, courseNumber);
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void Insert(Course course) {
        root = insert(root, course);
    }

    void PrintAll() const {
        inOrder(root);
    }

    Course* Search(string courseNumber) const {
        Node* result = search(root, courseNumber);
        if (result != nullptr) {
            return &(result->course);
        }
        return nullptr;
    }
};


// Utility Functions


// Convert string to uppercase
string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Trim whitespace
string trim(string str) {
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    return str;
}


// Load Data

void loadDataStructure(string fileName, BinarySearchTree& bst) {

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }

        if (tokens.size() < 2) {
            cout << "Invalid format detected in file." << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        for (size_t i = 2; i < tokens.size(); i++) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        bst.Insert(course);
    }

    file.close();
    cout << "Data successfully loaded." << endl;
}


// Print Single Course

void printCourse(BinarySearchTree& bst) {

    string courseNumber;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    courseNumber = toUpperCase(courseNumber);

    Course* course = bst.Search(courseNumber);

    if (course == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    cout << course->courseNumber << ", "
        << course->courseTitle << endl;

    if (!course->prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course->prerequisites.size(); i++) {
            cout << course->prerequisites[i];
            if (i < course->prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    else {
        cout << "No prerequisites." << endl;
    }
}


// Main Program

int main() {

    BinarySearchTree bst;
    string fileName;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {

        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input." << endl;
            continue;
        }

        switch (choice) {

        case 1:
            cout << "Enter file name: ";
            cin >> fileName;
            loadDataStructure(fileName, bst);
            break;

        case 2:
            cout << "Here is a sample schedule:" << endl;
            bst.PrintAll();
            break;

        case 3:
            printCourse(bst);
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}