#include<iostream>
#include "Mark.h"

Mark::Mark():studentId(""), courseCode(""), componentId(""), marksObtained(0){
}

Mark::Mark(const string &studId, const string &courseCode, const string &compId, double mark)
    :studentId(studId), courseCode(courseCode), componentId(compId), marksObtained(mark){
}

string Mark::getStudentId() const{
    return studentId;
}

string Mark::getCourseCode() const{
    return courseCode;
}

string Mark::getComponentId() const{
    return componentId;
}

double Mark::getMarksObtained() const{
    return marksObtained;
}

void Mark::setMarksObtained(double m){
    marksObtained = m;
}

