#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <string>
using std::string;

//abstract class(cannot be instantiated directly)
class Component{
    protected:
        string courseCode;
        string componentId;
        string componentName;
        double maxMarks;
        double weightage;
    public:
        Component();
        Component(const string &courseCode, const string &componentId, const string &componentName, double maxMarks, double weightage);

        //virtual destructor ensures derived class destructors run correctly when deleted through a Component pointer
        virtual ~Component();

        string getCourseCode() const;
        string getComponentId() const;
        string getComponentName() const;
        double getMaxMarks() const;
        double getWeightage() const;

        //pure virtual functions means every derived component type must define its own implementation
        virtual string getType() const =0;
        virtual double calculateWeightedScore(double marksObtained) const =0;

        //derived classes may override if needed
        virtual void display() const;

};

#endif // COMPONENT_H_INCLUDED
