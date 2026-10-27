#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include<iostream>
#include<string>
#include "Person.h"
#include "Mark.h"
#include "Course.h"
using std::ostream;
using std::string;

const int MAX_RECORDS = 50;

//a student, built on top of Person, holds all their mark records
class Student: public Person{
    private:
        Mark markRecords[MAX_RECORDS];
        int recordCount;

    public:
        Student();
        Student(const string &studId, const string &studName);
        ~Student() override;

        //student mark records management
        bool addMark(const Mark &m);
        bool hasMarkFor(const string &courseCode, const string &componentId) const;
        bool updateMark(const string &courseCode, const string &componentId, double newMarksObtained);
        int getRecordCount() const;
        Mark getRecordAt(int index) const;

        //true if student has at least one mark recorded for this course
        bool isEnrolledIn(const string &courseCode) const;

        //final grade calculation for each course
        double calculateOverallMark(const Course &c) const;
        void convertToGrade(const Course &c, string &grade, double &gradePoint) const;

        void displayInfo() const override;

        //compares students by id
        bool operator==(const Student &other) const;

        //friend lets cout << student read private data without getters
        friend ostream& operator<<(ostream& os, const Student& student);

};


#endif // STUDENT_H_INCLUDED
