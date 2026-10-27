#ifndef COURSE_H_INCLUDED
#define COURSE_H_INCLUDED

#include "Component.h"
#include<string>
using std::string;

const int MAX_COMPONENTS = 50;

class Course{
    private:
        string courseCode;
        string courseName;
        int creditHour;

        //composition: course owns its components
        //Component pointers are used because Component is abstract and components are polymorphic
        Component *components[MAX_COMPONENTS];
        int componentCount;

    public:
        Course();
        Course(const string &courseCode, const string &courseName, int creditHour);

        //deletes every component this course owns(Course is responsible for their lifetime)
        ~Course();

        string getCourseCode() const;
        void setCourseName(const string &courseName);
        string getCourseName() const;
        void setCreditHour(int creditHour);
        int getCreditHour() const;

        //adds a component to the course, returns false if MAX_COMPONENTS has been reached
        bool addComponent(Component *comp);
        Component *getComponentByIndex(int index) const;
        Component *getComponentById(const string &componentId) const;
        int getComponentCount() const;

        //allows a component to be added to a course using course += component
        Course &operator+=(Component *comp);

        //compares two courses by course code only, used to detect duplicates when loading or adding a course
        bool operator==(const Course &other) const;


        void displayCourse() const;


};


#endif // COURSE_H_INCLUDED




