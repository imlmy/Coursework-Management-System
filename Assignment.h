#ifndef ASSIGNMENT_H_INCLUDED
#define ASSIGNMENT_H_INCLUDED

#include<string>
#include "Component.h"
using std::string;

class Assignment: public Component{
    public:
        Assignment();
        Assignment(const string &code, const string &id, const string &name, double maxMarks, double weightage);
        string getType() const override;
        double calculateWeightedScore(double marksObtained) const override;
};


#endif // ASSIGNMENT_H_INCLUDED
