#include "Component.h"
#include "Assignment.h"
#include<iostream>
using std::cout;

Assignment::Assignment(): Component(){
}

Assignment::Assignment(const string &code, const string &id, const string &name, double maxMarks, double weightage)
    : Component(code,id,name,maxMarks,weightage){
}

string Assignment::getType() const{
    return "Assignment";
}

double Assignment::calculateWeightedScore(double marksObtained) const{
    if(maxMarks == 0){
        return 0.0;
    }
    return (marksObtained/maxMarks) * weightage;
}
