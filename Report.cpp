#include <iostream>
#include <iomanip>
#include "Report.h"
using std::cout;
using std::endl;
using std::setw;
using std::left;

Report::Report(): title("Coursework Performance Report"){
}

Report::Report(const string &title)
    : title(title) {
}

void Report::printStudentReport(const Student &s, Course* const courses[], int courseCount) const {
    cout << "\n===================================================================================" << endl;
    cout << "Report for (" << s.getId() << ") " << s.getName() << endl;
    cout << "===================================================================================" << endl;
    cout << left << setw(10) << "Code" << setw(30) << "Course" << setw(10) << "Credit" << setw(10) << "Score" << setw(10) << "Grade" << "Grade Point" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;

    //only prints courses the student is actually enrolled in
    for(int i=0; i<courseCount; i++) {
        if (s.isEnrolledIn(courses[i]->getCourseCode())) {
            string grade;
            double point;
            s.convertToGrade(*courses[i], grade, point);
            double score = s.calculateOverallMark(*courses[i]);

            cout << left << setw(10) << courses[i]->getCourseCode()
                 << setw(30) << courses[i]->getCourseName()
                 << setw(10) << courses[i]->getCreditHour()
                 << setw(10) << score
                 << setw(10) << grade
                 << point << endl;
        }
    }

    cout << "===================================================================================" << endl;
}

void Report::printClassReport(const Course &c, Student * const students[], int studentCount) const {
    cout << "==========================================================" << endl;
    cout << "Class Report for: " << c.getCourseCode() << " - " << c.getCourseName() << endl;
    cout << "==========================================================" << endl;
    cout << left << setw(12) << "Student ID" << setw(20) << "Name" << setw(10) << "Score" << "Grade" << endl;
    cout << "----------------------------------------------------------" << endl;

    double total = 0.0;
    double highest = -1.0;
    double lowest = -1.0;
    int enrolledCount = 0;

    //loops through all students, only counts those enrolled in this course
    for(int i = 0; i < studentCount; i++) {
        if(students[i]->isEnrolledIn(c.getCourseCode())) {
            string grade;
            double point;
            students[i]->convertToGrade(c, grade, point);
            double score = students[i]->calculateOverallMark(c);

            cout << left << setw(12) << students[i]->getId()
                 << setw(20) << students[i]->getName()
                 << setw(10) << score
                 << grade << endl;

            total += score;
            //track running highest/lowest as scores come in
            if (enrolledCount == 0 || score > highest) highest = score;
            if (enrolledCount == 0 || score < lowest) lowest = score;
            enrolledCount++;
        }
    }

    cout << "----------------------------------------------------------" << endl;
    if(enrolledCount == 0) {
        cout << "No students enrolled in this course." << endl;
    }else {
        cout << "Average: " << (total/enrolledCount) << endl;
        cout << "Highest: " << highest << endl;
        cout << "Lowest : " << lowest << endl;
    }
    cout << "==========================================================" << endl;
}
