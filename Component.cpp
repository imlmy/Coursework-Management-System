#include<iostream>
#include "Component.h"
using std::cout;
using std::endl;

Component::Component()
    : courseCode(""), componentId(""), componentName(""), maxMarks(0.0), weightage(0.0){
}

Component::Component(const string &courseCode, const string &componentId, const string &componentName, double maxMarks, double weightage)
    : courseCode(courseCode), componentId(componentId), componentName(componentName), maxMarks(maxMarks), weightage(weightage){
}

Component::~Component(){
}

string Component::getCourseCode() const{
    return courseCode;
}

string Component::getComponentId() const{
    return componentId;
}
string Component::getComponentName() const{
    return componentName;
}

double Component::getMaxMarks() const{
    return maxMarks;
}

double Component::getWeightage() const{
    return weightage;
}

void Component::display() const{
    cout << "Component: " << componentId << " " << componentName << " (Type: " << getType() << ", Maximum Marks: " << maxMarks << ", Weightage: " << weightage << "%)" << endl;
}
