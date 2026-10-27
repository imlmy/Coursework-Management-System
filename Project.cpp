#include "Component.h"
#include "Project.h"
#include<string>
using std::string;

Project::Project(): Component(){
}

Project::Project(const string &code, const string &id, const string &name, double maxMarks, double weightage)
    : Component(code,id,name,maxMarks,weightage){
}

string Project::getType() const{
    return "Project";
}

double Project::calculateWeightedScore(double marksObtained) const{
    if(maxMarks == 0){
        return 0.0;
    }
    return (marksObtained/maxMarks) * weightage;
}
