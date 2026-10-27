#include <iostream>
#include <fstream>
#include <sstream>
#include "SystemController.h"
#include "Report.h"
#include "Assignment.h"
#include "Quiz.h"
#include "Project.h"
#include "FinalExam.h"
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;

SystemController::SystemController(): courseCount(0), studentCount(0){
}

SystemController::~SystemController(){
    //deletes every course and student the system owns
    for(int i=0; i<courseCount; i++){
        delete courses[i];
    }
    for(int i=0; i<studentCount; i++){
        delete students[i];
    }
}

//reads course.txt, one course per line
void SystemController::loadCourses(const string &filename){
    ifstream infile(filename);
    if(!infile){
        cout << "Could not open " << filename << endl;
        return;
    }

    string line;
    while(std::getline(infile, line)){
        if(line.empty()){
            continue;
        }
        if(courseCount >= MAX_COURSES){
            cout << "Course limit reached!" << endl;
            break;
        }

        stringstream ss(line);
        string code, name, creditStr;
        std::getline(ss, code, ';');
        std::getline(ss, name, ';');
        std::getline(ss, creditStr, ';');

        int credit = 0;
        stringstream(creditStr) >> credit;

        Course *newCourse = new Course(code, name, credit);

        //skip if this course code was already loaded
        //demonstrates Course::operator== on real, file-sourced data
        bool duplicate = false;
        for(int i=0; i<courseCount; i++){
            if(*courses[i] == *newCourse){
                duplicate = true;
                break;
            }
        }

        if(duplicate){
            cout << "Duplicate course code " << code << " in " << filename << "!" << endl;
            delete newCourse;
            continue;
        }

        courses[courseCount] = newCourse;
        courseCount++;
    }

    infile.close();
}

//picks the derived Component type by matching keywords in the component name because components.txt has no explicit type field
Component *SystemController::createComponent(const string &courseCode, const string &id, const string &name, double maxMarks, double weightage) const{
    string lowerName = name;
    for(size_t i=0; i<lowerName.size(); i++){
        lowerName[i] = tolower(lowerName[i]);
    }

    if(lowerName.find("quiz")!=string::npos || lowerName.find("lab")!=string::npos|| lowerName.find("test")!=string::npos || lowerName.find("midterm") != string::npos){
        return new Quiz(courseCode, id, name, maxMarks, weightage); //Lab Test/Midterm Exam is a kind of Quiz
    }else if(lowerName.find("project")!=string::npos){
        return new Project(courseCode, id, name, maxMarks, weightage);
    }else if(lowerName.find("exam")!=string::npos){
        return new FinalExam(courseCode, id, name, maxMarks, weightage);
    }else{
        return new Assignment(courseCode, id, name, maxMarks, weightage);   //Assignment/Assignment 1/2/3 is Assignment
    }
}

//reads components.txt, attaches each component to its course
void SystemController::loadComponents(const string &filename){
    ifstream infile(filename);
    if(!infile) {
        cout << "Could not open " << filename << endl;
        return;
    }

    string line;
    while(std::getline(infile, line)){
        if(line.empty()){
            continue;
        }

        stringstream ss(line);
        string courseCode, componentId, componentName, maxMarksStr, weightageStr;
        std::getline(ss, courseCode, ';');
        std::getline(ss, componentId, ';');
        std::getline(ss, componentName, ';');
        std::getline(ss, maxMarksStr, ';');
        std::getline(ss, weightageStr, ';');

        double maxMarks = 0.0, weightage = 0.0;
        stringstream(maxMarksStr) >> maxMarks;
        stringstream(weightageStr) >> weightage;

        Course *course = findCourse(courseCode);
        if(course==nullptr) {
            cout << "Component " << componentId << " refers to unknown course " << courseCode << endl;
            continue;
        }

        Component *comp = createComponent(courseCode, componentId, componentName, maxMarks, weightage);
        *course += comp;
    }

    infile.close();
}

//reads student.txt, one student per line
void SystemController::loadStudents(const string &filename){
    ifstream infile(filename);
    if(!infile.is_open()) {
        cout << "Could not open " << filename << endl;
        return;
    }

    string line;
    while(std::getline(infile, line)){
        if(line.empty()) continue;
        if(studentCount >= MAX_STUDENTS){
            cout << "Student limit reached! " << endl;
            break;
        }

        stringstream ss(line);
        string id, name;
        std::getline(ss, id, ';');
        std::getline(ss, name, ';');

        Student *newStudent = new Student(id, name);

        //skip if this student ID was already loaded
        //demonstrates Student::operator== on real, file-sourced data
        bool duplicate = false;
        for(int i=0; i<studentCount; i++){
            if (*students[i] == *newStudent){
                duplicate = true;
                break;
            }
        }

        if(duplicate){
            cout << "Duplicate student ID " << id << " in " << filename << "!" << endl;
            delete newStudent;
            continue;
        }

        students[studentCount] = newStudent;
        studentCount++;
    }

    infile.close();
}

//reads marks.txt, attaches each mark to the matching student
void SystemController::loadMarks(const string &filename){
    ifstream infile(filename);
    if(!infile.is_open()){
        cout << "Could not open " << filename << endl;
        return;
    }

    string line;
    while(std::getline(infile, line)){
        if(line.empty()) continue;

        stringstream ss(line);
        string studentId, courseCode, componentId, marksStr;
        std::getline(ss, studentId, ';');
        std::getline(ss, courseCode, ';');
        std::getline(ss, componentId, ';');
        std::getline(ss, marksStr, ';');

        double marksObtained = 0.0;
        stringstream(marksStr) >> marksObtained;

        Student *student = findStudent(studentId);
        if (student == nullptr){
            cout << "Mark refers to unknown student " << studentId << endl;
            continue;
        }

        Mark m(studentId, courseCode, componentId, marksObtained);
        student->addMark(m);
    }

    infile.close();
}

//writes every course back to course.txt
void SystemController::saveCourses(const string &filename) const {
    ofstream outfile(filename.c_str());
    if(!outfile.is_open()){
        cout << "Could not open " << filename << " for saving." << endl;
        return;
    }

    for(int i = 0; i < courseCount; i++){
        outfile << courses[i]->getCourseCode() << ";" << courses[i]->getCourseName() << ";" << courses[i]->getCreditHour() << endl;
    }

    outfile.close();
}

//writes every course's components back to components.txt
void SystemController::saveComponents(const string &filename) const {
    ofstream outfile(filename.c_str());
    if(!outfile.is_open()) {
        cout << "Could not open " << filename << " for saving." << endl;
        return;
    }

    for(int i = 0; i < courseCount; i++){
        int compCount = courses[i]->getComponentCount();
        for (int j = 0; j < compCount; j++){
            Component *comp = courses[i]->getComponentByIndex(j);
            outfile << courses[i]->getCourseCode() << ";" << comp->getComponentId() << ";"
                    << comp->getComponentName() << ";" << comp->getMaxMarks() << ";"
                    << comp->getWeightage() << endl;
        }
    }

    outfile.close();
}

//writes every student back to student.txt
void SystemController::saveStudents(const string &filename) const{
    ofstream outfile(filename.c_str());
    if(!outfile.is_open()) {
        cout << "Could not open " << filename << " for saving." << endl;
        return;
    }

    for(int i = 0; i < studentCount; i++){
        outfile << students[i]->getId() << ";" << students[i]->getName() << endl;
    }

    outfile.close();
}

//writes every student's mark records back to marks.txt
void SystemController::saveMarks(const string &filename) const {
    ofstream outfile(filename.c_str());
    if(!outfile.is_open()) {
        cout << "Could not open " << filename << " for saving." << endl;
        return;
    }

    for(int i = 0; i < studentCount; i++) {
        int recordCount = students[i]->getRecordCount();
        for (int j = 0; j < recordCount; j++) {
            Mark m = students[i]->getRecordAt(j);
            outfile << m.getStudentId() << ";" << m.getCourseCode() << ";" << m.getComponentId() << ";" << m.getMarksObtained() << endl;
        }
    }

    outfile.close();
}

//saves all four files in one call, done once at program exit
void SystemController::saveAll(const string &courseFile, const string &studentFile,
                                const string &marksFile, const string &componentFile) const {
    saveCourses(courseFile);
    saveComponents(componentFile);
    saveStudents(studentFile);
    saveMarks(marksFile);
    cout << "All data saved (" << courseFile << ", " << componentFile << ", " << studentFile << ", " << marksFile << ")." << endl;
}

Course *SystemController::findCourse(const string &code) const{
    for(int i=0; i<courseCount; i++){
        if(courses[i]->getCourseCode() == code){
            return courses[i];
        }
    }
    return nullptr;
}


Student *SystemController::findStudent(const string &id) const{
    for(int i=0; i<studentCount; i++){
        if (students[i]->getId() == id){
            return students[i];
        }
    }
    return nullptr;
}

void SystemController::listCourses() const {
    cout << "\n=======================List of Courses=======================\n";
    for(int i=0; i<courseCount; i++){
        cout << "\n[" << i+1 << "] ";
        courses[i]->displayCourse();
    }
}

void SystemController::listStudents() const {
    cout << "\n====================List of Students====================\n";
    for(int i=0; i<studentCount; i++){
        cout << "[" << i+1 << "] " <<  *students[i] << endl;   //friend operator<< overload
    }
}

//prompts for course details and adds it if the code isn't already used
void SystemController::addNewCourse() {
    if(courseCount >= MAX_COURSES){
        cout << "Cannot add more courses. Limit reached!" << endl;
        return;
    }

    string code, name;
    int credit;
    cout << "\nEnter course code: ";
    cin >> code;
    cout << "Enter course name: ";
    cin.ignore();
    std::getline(cin, name);
    cout << "Enter credit hours: ";
    cin >> credit;

    Course newCourse(code, name, credit);
    for(int i = 0; i < courseCount; i++){
        if (*courses[i] == newCourse) {  // operator== overload to checks for duplicate course code
            cout << "A course with this code already exists." << endl;
            return;
        }
    }

    courses[courseCount] = new Course(code, name, credit);
    courseCount++;
    cout << "Course added." << endl;
}

//lets the lecturer update an existing course's name/credit hour
void SystemController::editCourse(){
    string code;
    cout << "Enter course code to edit: ";
    cin >> code;

    Course *course = findCourse(code);
    if(course == nullptr){
        cout << "Course not found!" << endl;
        return;
    }

    cout << "Current name: " << course->getCourseName() << endl;
    cout << "Current credit hour: " << course->getCreditHour() << endl;

    string newName;
    int newCredit;
    cout << "Enter new course name: ";
    cin.ignore();
    std::getline(cin, newName);
    cout << "Enter new credit hour: ";
    cin >> newCredit;

    //course code is intentionally not editable because marks.txt records reference courses by course code
    course->setCourseName(newName);
    course->setCreditHour(newCredit);
    cout << "Course updated." << endl;
}

//prompts for a component's details, builds it, and attaches it to the course
void SystemController::defineComponent() {
    cout << "\n==========Define Component==========\n";
    string courseCode;
    cout << "Enter course code: ";
    cin >> courseCode;

    Course *course = findCourse(courseCode);
    if(course == nullptr){
        cout << "Course not found!" << endl;
        return;
    }

    string id, name;
    double maxMarks, weightage;
    cout << "Enter component ID: ";
    cin >> id;

    if(course->getComponentById(id) != nullptr){
        cout << "A component with this ID already exists in this course." << endl;
        return;
    }

    cout << "Enter component name: ";
    cin.ignore();
    std::getline(cin, name);
    cout << "Enter max marks: ";
    cin >> maxMarks;
    cout << "Enter weightage (%): ";
    cin >> weightage;

    Component *comp = createComponent(courseCode, id, name, maxMarks, weightage);
    *course += comp;
    cout << "Component added." << endl;
}

//submenu for adding or editing a course
void SystemController::manageCourse(){
    cout << "\n==========Manage Course==========\n";
    cout << "1. Add Course" << endl;
    cout << "2. Edit Course" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    switch(choice) {
        case 1:
            addNewCourse();
            break;
        case 2:
            editCourse();
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
}

//prompts for student details and adds it if the ID isn't already used
void SystemController::addNewStudent() {
    if(studentCount >= MAX_STUDENTS){
        cout << "Cannot add more students. Limit reached!" << endl;
        return;
    }

    string id, name;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter student name: ";
    cin.ignore();
    std::getline(cin, name);

    Student newStudent(id, name);
    for(int i = 0; i < studentCount; i++){
        if (*students[i] == newStudent) {   // operator== overload (checks for duplicate student ID)
            cout << "A student with this ID already exists." << endl;
            return;
        }
    }

    students[studentCount] = new Student(id, name);
    studentCount++;
    cout << "Student added." << endl;
}

//lets the lecturer rename an existing student
void SystemController::editStudent(){
    string id;
    cout << "Enter student ID to edit: ";
    cin >> id;

    Student *student = findStudent(id);
    if(student == nullptr){
        cout << "Student not found!" << endl;
        return;
    }

    cout << "Current name: " << student->getName() << endl;

    string newName;
    cout << "Enter new student name: ";
    cin.ignore();
    std::getline(cin, newName);

    // Student ID is intentionally not editable because marks.txt records references students by ID
    student->setName(newName);
    cout << "Student updated." << endl;
}

//submenu for adding or editing a student
void SystemController::manageStudent(){
    cout << "\n==========Manage Student==========\n";
    cout << "1. Add Student" << endl;
    cout << "2. Edit Student" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            addNewStudent();
            break;
        case 2:
            editStudent();
            break;
        default:
            cout << "Invalid choice!" << endl;
             break;
    }
}

//enters a new mark, or updates it if one already exists
void SystemController::manageMark(){
    string studentId, courseCode, componentId;
    double marks;

    cout << "\n==========Enter/Update Marks==========\n";
    cout << "Enter student ID: ";
    cin >> studentId;
    Student *student = findStudent(studentId);
    if(student == nullptr){
        cout << "Student not found!" << endl;
        return;
    }

    cout << "Enter course code: ";
    cin >> courseCode;
    Course *course = findCourse(courseCode);
    if(course == nullptr){
        cout << "Course not found!" << endl;
        return;
    }

    cout << "Enter component ID: ";
    cin >> componentId;
    Component *comp = course->getComponentById(componentId);
    if(comp == nullptr){
        cout << "Component not found in that course." << endl;
        return;
    }

    cout << "Enter marks obtained (max " << comp->getMaxMarks() << "): ";
    cin >> marks;

    if(student->hasMarkFor(courseCode, componentId)){
        student->updateMark(courseCode, componentId, marks);
        cout << "Mark updated." << endl;
    }else{
        Mark m(studentId, courseCode, componentId, marks);
        student->addMark(m);
        cout << "Mark added." << endl;
    }
}

//prints one student's report across all their courses
void SystemController::generateReport() const{
    string studentId;
    cout << "Enter student ID for report: ";
    cin >> studentId;

    Student *student = findStudent(studentId);
    if(student == nullptr){
        cout << "Student not found!" << endl;
        return;
    }

    Report report("Coursework Performance Report (student)");
    report.printStudentReport(*student, courses, courseCount);
}

//prints all students' results for one course
void SystemController::generateClassReport() const {
    string courseCode;
    cout << "Enter course code for class report: ";
    cin >> courseCode;

    Course *course = findCourse(courseCode);
    if(course == nullptr){
        cout << "Course not found!" << endl;
        return;
    }

    Report report("Coursework Performance Report (class)");
    report.printClassReport(*course, students, studentCount);
}

//main menu loop, keeps running until the lecturer picks 0
void SystemController::showMenu(){
    int choice = -1;

    while (choice != 0) {
        cout << "\n------ Coursework Management System ------" << endl;
        cout << "1. List Courses" << endl;
        cout << "2. List Students" << endl;
        cout << "3. Manage Course" << endl;
        cout << "4. Manage Student" << endl;
        cout << "5. Define Component" << endl;
        cout << "6. Enter/Update Mark" << endl;
        cout << "7. Generate Student Report" << endl;
        cout << "8. Generate Class Report" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listCourses();
                break;
            case 2:
                listStudents();
                break;
            case 3:
                manageCourse();
                break;
            case 4:
                manageStudent();
                break;
            case 5:
                defineComponent();
                break;
            case 6:
                manageMark();
                break;
            case 7:
                generateReport();
                break;
            case 8:
                generateClassReport();
                break;
            case 0:
                cout << "Exiting the system..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again!" << endl;
                break;
        }
    }
}
