#ifndef QUIZ_H_INCLUDED
#define QUIZ_H_INCLUDED

#include<string>
#include "Component.h"
using std::string;


class Quiz: public Component{
    public:
        Quiz();
        Quiz(const string &code, const string &id, const string &name, double maxMarks, double weightage);
        string getType() const override;
        double calculateWeightedScore(double marksObtained) const override ;


};

#endif // QUIZ_H_INCLUDED
