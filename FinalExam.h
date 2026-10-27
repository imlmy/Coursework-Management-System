#ifndef FINALEXAM_H_INCLUDED
#define FINALEXAM_H_INCLUDED

#include<string>
#include "Component.h"
using std::string;


class FinalExam: public Component{
    public:
        FinalExam();
        FinalExam(const string &code, const string &id, const string &name, double maxMarks, double weightage);
        string getType() const override;
        double calculateWeightedScore(double marksObtained)const override;
};

#endif // FINALEXAM_H_INCLUDED
