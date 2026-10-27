#ifndef REPORT_H_INCLUDED
#define REPORT_H_INCLUDED

#include <string>
#include "Student.h"
#include "Course.h"
using std::string;

//builds and prints performance reports, doesn't store any report data itself
class Report {
    private:
        string title;

    public:
        Report();
        Report(const string &title);

        //prints one student's marks and grade across every course they're enrolled in
        void printStudentReport(const Student &s, Course* const courses[], int courseCount) const;

        //prints all students' results for one course, plus class average, highest, and lowest
        void printClassReport(const Course &c, Student* const students[], int studentCount) const;

};


#endif // REPORT_H_INCLUDED
