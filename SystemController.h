#ifndef SYSTEMCONTROLLER_H_INCLUDED
#define SYSTEMCONTROLLER_H_INCLUDED

#include <string>
#include "Course.h"
#include "Student.h"
using std::string;

const int MAX_COURSES = 50;
const int MAX_STUDENTS = 50;

//coordinates the whole system: loading, saving, and the menu
class SystemController{
    private:
        //composition: system owns all courses and students
        Course *courses[MAX_COURSES];
        int courseCount;

        Student *students[MAX_STUDENTS];
        int studentCount;

        //builds the right derived Component type from a component name
        Component *createComponent(const string &courseCode, const string &id, const string &name, double maxMarks, double weightage) const;

        //internal helpers used by manageCourse() and manageStudent()
        void addNewCourse();
        void editCourse();
        void addNewStudent();
        void editStudent();

    public:
        SystemController();
        ~SystemController();

        //file input output
        void loadCourses(const string &filename);
        void loadComponents(const string &filename);
        void loadStudents(const string &filename);
        void loadMarks(const string&filename);
        void saveCourses(const string &filename) const;
        void saveComponents(const string &filename) const;
        void saveStudents(const string &filename) const;
        void saveMarks(const string &filename) const;
        void saveAll(const string &courseFile, const string &studentFile, const string &marksFile, const string &componentFile) const;

        Course *findCourse(const string &code) const;
        Student *findStudent(const string &id) const;

        void listCourses() const;
        void listStudents() const;
        void manageCourse();
        void defineComponent();
        void manageStudent();
        void manageMark();
        void generateReport() const;
        void generateClassReport() const;

        void showMenu();
};


#endif // SYSTEMCONTROLLER_H_INCLUDED
