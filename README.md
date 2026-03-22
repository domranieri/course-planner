# C++ Course Planner

A console based course planner that stores and retrieves course information using a binary search tree. Load course data from a CSV file, browse all courses in alphabetical order, or search for a specific course to view its title and prerequisites

---

## How to Build & Run

### Visual Studio (Windows)
1. Create a new **Empty Project**
2. Add `main.cpp`, `BinarySearchTree.cpp`, `BinarySearchTree.h`, and `Course.h`
3. Set **C++ Language Standard** to C++11 or later *(Project → Properties → C/C++ → Language)*
4. Build and run

---

## CSV File Format

Each line in the input file represents one course:

```
CourseNumber,CourseTitle[,Prerequisite1,Prerequisite2,...]
```

- The first two fields (course number and title) are required
- Prerequisites are optional and comma separated after the title
- Blank lines and lines missing required fields are skipped with a warning

**Example (`courses.csv`):**
```
CS101,Introduction to Programming
CS201,Data Structures,CS101
CS301,Algorithms,CS201
MATH201,Discrete Mathematics,MATH101
CS401,Operating Systems,CS301,MATH201
```

---

## Example Session

```
Welcome to the Course Planner.

  1. Load Data Structure
  2. Print Course List
  3. Print Course
  9. Exit
What would you like to do? 1
Enter file name: courses.csv
Data loaded: 5 course(s).

What would you like to do? 2
Here is a sample schedule (5 courses):
CS101, Introduction to Programming
CS201, Data Structures
CS301, Algorithms
CS401, Operating Systems
MATH201, Discrete Mathematics

What would you like to do? 3
What course do you want to know about? cs301
CS301, Algorithms
Prerequisites: CS201

What would you like to do? 9
Thank you for using the Course Planner!
```
