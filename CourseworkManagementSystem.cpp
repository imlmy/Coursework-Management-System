#include "SystemController.h"

int main(){
    //single object created here, not a dummy main
    SystemController sys;

    //files are read exactly once at startup
    sys.loadCourses("course.txt");
    sys.loadComponents("components.txt");
    sys.loadStudents("student.txt");
    sys.loadMarks("marks.txt");

    //all user interaction and in-memory processing happens here
    sys.showMenu();

    //files are saved exactly once, right before the program terminates
    sys.saveAll("course.txt", "student.txt", "marks.txt", "components.txt");

    return 0;
}
