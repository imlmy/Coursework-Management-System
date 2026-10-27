#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

#include<string>
#include "Component.h"
using std::string;


class Project: public Component{
    public:
        Project();
        Project(const string &code, const string &id, const string &name, double maxMarks, double weightage);
        string getType() const override;
        double calculateWeightedScore(double marksObtained) const override;

};

#endif // PROJECT_H_INCLUDED
