#include <iostream>
#include "Course.h"
using std::cout;
using std::endl;

Course::Course() : courseCode(""), courseName(""), creditHour(0), componentCount(0){
    //fill array with nullptr, no components yet
    for(int i=0; i<MAX_COMPONENTS; i++) {
        components[i] = nullptr;
    }
}

Course::Course(const string &courseCode, const string &courseName, int creditHour)
    : courseCode(courseCode), courseName(courseName), creditHour(creditHour), componentCount(0){
    for(int i=0; i<MAX_COMPONENTS; i++) {
        components[i] = nullptr;
    }
}

Course::~Course(){
    //course owns its components, so it deletes them
    for(int i=0; i<componentCount; i++){
        delete components[i];
        components[i] = nullptr;
    }
}

string Course::getCourseCode() const{
    return courseCode;
}

void Course::setCourseName(const string &courseName){
    this->courseName = courseName;
}

string Course::getCourseName() const{
    return courseName;
}

void Course::setCreditHour(int creditHour){
    this->creditHour = creditHour;
}

int Course::getCreditHour() const{
    return creditHour;
}

bool Course::addComponent(Component *comp){
    //reject if array is already full
    if(componentCount>=MAX_COMPONENTS){
        cout << "Component has reached the maximum limit of " << MAX_COMPONENTS << endl;
        return false;
    }
    components[componentCount] = comp;
    componentCount++;
    return true;
}

Component *Course::getComponentByIndex(int index) const{
    if(index<0 || index>=componentCount) {
        return nullptr;
    }
    return components[index];
}

Component *Course::getComponentById(const string &componentId) const{
    for(int i=0; i<componentCount; i++) {
        if(components[i]->getComponentId() == componentId) {
            return components[i];
        }
    }
    return nullptr;
}

int Course::getComponentCount() const{
    return componentCount;
}

Course &Course::operator+=(Component *comp){
    //if add fails (array full), delete comp so it isn't leaked
    bool added = addComponent(comp);
    if(!added){
        delete comp;
    }
    return *this;
}

bool Course::operator==(const Course &other) const {
    return courseCode == other.courseCode;
}

void Course::displayCourse() const {
    cout << "Course: " << courseCode << " " << courseName << " (" << creditHour << " credit hours)" << endl;
    for (int i = 0; i < componentCount; i++) {
        components[i]->display();
    }
}
