#include "Component.h"
#include "FinalExam.h"
#include<string>
using std::string;

FinalExam::FinalExam(): Component(){
}

FinalExam::FinalExam(const string &code, const string &id, const string &name, double maxMarks, double weightage)
    : Component(code,id,name,maxMarks,weightage){
}

string FinalExam::getType() const{
    return "Final Exam";
}

double FinalExam::calculateWeightedScore(double marksObtained) const{
    if(maxMarks == 0){
        return 0.0;
    }
    return (marksObtained/maxMarks) * weightage;
}
