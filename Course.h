// Course.h
#ifndef COURSE_H_
#define COURSE_H_

#include <string>
#include <vector>

struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

#endif // COURSE_H_