#ifndef MARK_H_INCLUDED
#define MARK_H_INCLUDED

#include<iostream>
#include<string>
using std::string;
using std::ostream;

//one mark a student achieved for one component in a course
class Mark{
    private:
        string studentId;
        string courseCode;
        string componentId;
        double marksObtained;

    public:
        Mark();
        Mark(const string &studId, const string &courseCode,const string &ompId, double mark);

        string getStudentId() const;
        string getCourseCode() const;
        string getComponentId() const;
        double getMarksObtained() const;
        void setMarksObtained(double m);
};


#endif // MARK_H_INCLUDED
