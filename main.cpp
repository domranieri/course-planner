// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm>
#include "BinarySearchTree.h"
#include "Course.h"

// String utilities

// Uppercase conversion
static std::string toUpperCase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Trim leading and trailing whitespace
static std::string trim(const std::string& str) {
    const std::string whitespace = " \t\r\n";
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

// loadDataStructure
// Reads a CSV file where each line is: CourseNumber,CourseTitle[,Prereq1,Prereq2,...]

static void loadDataStructure(const std::string& fileName, BinarySearchTree& bst) {

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "Error: Unable to open \"" << fileName << "\". "
                  << "Check that the file exists and the path is correct.\n";
        return;
    }

    int loaded  = 0;
    int skipped = 0;
    std::string line;

    while (std::getline(file, line)) {

        // Skip blank lines
        if (trim(line).empty()) continue;

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }

        if (tokens.size() < 2 || tokens[0].empty() || tokens[1].empty()) {
            std::cout << "  Skipping malformed line: " << line << "\n";
            ++skipped;
            continue;
        }

        Course course;
        course.courseNumber = toUpperCase(tokens[0]);
        course.courseTitle  = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(toUpperCase(tokens[i]));
            }
        }

        bst.Insert(course);
        ++loaded;
    }

    file.close();

    std::cout << "Data loaded: " << loaded << " course(s)";
    if (skipped > 0) {
        std::cout << ", " << skipped << " line(s) skipped due to formatting issues";
    }
    std::cout << ".\n";
}

// printCourse
// Prompts for a course number and prints its details if found

static void printCourse(const BinarySearchTree& bst) {

    std::string courseNumber;
    std::cout << "What course do you want to know about? ";
    std::cin >> courseNumber;
    courseNumber = toUpperCase(courseNumber);

    Course course = bst.Search(courseNumber);

    if (course.courseNumber.empty()) {
        std::cout << "Course \"" << courseNumber << "\" not found.\n";
        return;
    }

    std::cout << course.courseNumber << ", " << course.courseTitle << "\n";

    if (!course.prerequisites.empty()) {
        std::cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << course.prerequisites[i];
        }
        std::cout << "\n";
    } else {
        std::cout << "Prerequisites: None\n";
    }
}

// main

int main() {

    BinarySearchTree bst;
    std::string fileName;
    int choice = 0;

    std::cout << "Welcome to the Course Planner.\n";

    while (choice != 9) {

        std::cout << "\n";
        std::cout << "  1. Load Data Structure\n";
        std::cout << "  2. Print Course List\n";
        std::cout << "  3. Print Course\n";
        std::cout << "  9. Exit\n";
        std::cout << "What would you like to do? ";

        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a menu number.\n";
            continue;
        }

        switch (choice) {

        case 1:
            std::cout << "Enter file name: ";
            std::cin >> fileName;
            loadDataStructure(fileName, bst);
            break;

        case 2:
            if (bst.IsEmpty()) {
                std::cout << "No data loaded yet. Please use option 1 first.\n";
            } else {
                std::cout << "Here is a sample schedule (" << bst.Size() << " courses):\n";
                bst.PrintAll();
            }
            break;

        case 3:
            if (bst.IsEmpty()) {
                std::cout << "No data loaded yet. Please use option 1 first.\n";
            } else {
                printCourse(bst);
            }
            break;

        case 9:
            std::cout << "Thank you for using the Course Planner!\n";
            break;

        default:
            std::cout << choice << " is not a valid option.\n";
        }
    }

    return 0;
}
