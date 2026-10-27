#include<iostream>
#include "Student.h"
using std::cout;
using std::endl;
using std::ostream;

Student::Student(): Person(),recordCount(0){
}

Student::Student(const string &studId, const string &studName)
    :Person(studId, studName), recordCount(0){
}

Student::~Student(){
}

//adds a mark record, fails if array is full
bool Student::addMark(const Mark &m){
    if(recordCount >= MAX_RECORDS){
        cout << "Record has reached the maximum limit of " << MAX_RECORDS << endl;
        return false;
    }
    markRecords[recordCount] = m;
    recordCount++;
    return true;
}

//checks if a mark already exists for this course and component, used to avoid duplicate entries
bool Student::hasMarkFor(const string &courseCode, const string &componentId) const{
    for(int i=0; i<recordCount; i++){
        if(markRecords[i].getCourseCode() == courseCode && markRecords[i].getComponentId() == componentId){
            return true;
        }
    }
    return false;
}

//finds the matching mark record and overwrites its value
bool Student::updateMark(const string &courseCode, const string &componentId, double newMarksObtained){
    for(int i=0; i<recordCount; i++){
        if(markRecords[i].getCourseCode() == courseCode && markRecords[i].getComponentId() == componentId){
            markRecords[i].setMarksObtained(newMarksObtained);
            return true;
        }
    }
    return false;   //no existing record found
}

int Student::getRecordCount() const{
    return recordCount;
}

//returns the mark at index, or an empty Mark if index is invalid
Mark Student::getRecordAt(int index) const{
    if(index<0 || index >= recordCount){
        return Mark();
    }
    return markRecords[index];
}

//a student is "enrolled" in a course if they have at least one mark for it
bool Student::isEnrolledIn(const string &courseCode) const{
    for(int i=0; i<recordCount; i++){
        if(markRecords[i].getCourseCode() == courseCode){
            return true;
        }
    }
    return false;
}

//sums weighted score of every mark that belongs to this course, skips marks whose component no longer exists in the course
double Student::calculateOverallMark(const Course &c) const{
    double totalMark = 0.0;

    for(int i=0; i<recordCount; i++){
        if(markRecords[i].getCourseCode() == c.getCourseCode()){
            Component *comp = c.getComponentById(markRecords[i].getComponentId());
            if(comp!=nullptr){
                totalMark += comp->calculateWeightedScore(markRecords[i].getMarksObtained());
            }
        }
    }
    return totalMark;
}

//converts overall mark into a letter grade and grade point
void Student::convertToGrade(const Course &c, string &grade, double &gradePoint) const{
    double finalMark = calculateOverallMark(c);

    if(finalMark>=85){
        grade = "A+";
        gradePoint = 4.00;
    }else if(finalMark>=80){
        grade = "A";
        gradePoint = 4.00;
    }else if(finalMark>=75){
        grade = "A-";
        gradePoint = 3.67;
    }else if(finalMark>=70){
        grade = "B+";
        gradePoint = 3.33;
    }else if(finalMark>=65){
        grade = "B";
        gradePoint = 3.00;
    }else if(finalMark>=60){
        grade = "B-";
        gradePoint = 2.67;
    }else if(finalMark>=55){
        grade = "C+";
        gradePoint = 2.33;
    }else if(finalMark>=50){
        grade = "C";
        gradePoint = 2.00;
    }else if(finalMark>=40){
        grade = "D";
        gradePoint = 1.00;
    }else{
        grade = "F";
        gradePoint = 0.00;
    }
}

//overrides Person's version, shows record count instead of just id/name
void Student::displayInfo() const{
    cout << "Student ID: " <<getId() << "\tName: " << getName() << "\tTotal Mark Records: " << recordCount << endl;
}

//compares students by id
bool Student::operator==(const Student &other) const{
    return getId() == other.getId();
}

//friend function, prints id and name without needing public getters at the call site
ostream &operator<<(ostream& os, const Student &student){
    os << student.getId() <<  " " << student.getName();
    return os;
}
