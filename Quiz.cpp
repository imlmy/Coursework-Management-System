#include "Component.h"
#include "Quiz.h"
#include<string>
using std::string;

Quiz::Quiz(): Component(){
}

Quiz::Quiz(const string &code, const string &id, const string &name, double maxMarks, double weightage)
    : Component(code,id,name,maxMarks,weightage){
}

string Quiz::getType() const{
    return "Quiz";
}

double Quiz::calculateWeightedScore(double marksObtained) const{
    if(maxMarks == 0){
        return 0.0;
    }
    return (marksObtained/maxMarks) * weightage;
}
