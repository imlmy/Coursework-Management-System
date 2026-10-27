# Coursework Management System

A console-based C++ application for managing coursework assessment across multiple programming courses. The system keeps track of courses, assessment components and their weightages, student records, and marks, working out weighted overall results and letter grades automatically, and saving everything to text files between runs.

## Project Architecture

The program is organised into a header (`.h`) and implementation (`.cpp`) file for each class, plus a single main file:

### 1. Person.h / Person.cpp
* **Role:** Base class for anyone the system needs to identify by an ID and a name.
* **Content:**
  * Protected attributes for `id` and `name`.
  * Getters and setters, and a virtual `displayInfo()` that derived classes can override.

### 2. Student.h / Student.cpp
* **Role:** Represents an enrolled student, built on top of `Person`.
* **Content:**
  * Inherits from `Person` and adds a private array of `Mark` objects (composition) to hold every mark the student has recorded.
  * Functions to add a mark, check enrolment in a course, and calculate an overall mark and letter grade for a given course.
  * Overloads `operator==` to compare students by ID, and a friend `operator<<` to print a student's details directly through `cout`.

### 3. Component.h / Component.cpp
* **Role:** Abstract base class for any assessment component.
* **Content:**
  * Protected attributes shared by every component: course code, component ID, name, maximum marks, and weightage.
  * Pure virtual `getType()` and `calculateWeightedScore()`, so every derived component type must define how it identifies and scores itself.

### 4. Assignment.h/.cpp, Quiz.h/.cpp, Project.h/.cpp, FinalExam.h/.cpp
* **Role:** Concrete component types, each inheriting from `Component`.
* **Content:**
  * Each provides its own `getType()` and `calculateWeightedScore()` implementation.

### 5. Course.h / Course.cpp
* **Role:** Represents a single course and everything assessed within it.
* **Content:**
  * Holds a private array of `Component` pointers (composition), since a course is made up of its assessment components.
  * Functions to add and retrieve components by index or ID.
  * Overloads `operator+=` to add a component to a course, and `operator==` to compare courses by course code.

### 6. Mark.h / Mark.cpp
* **Role:** Represents a single mark obtained by a student for a component.
* **Content:**
  * Stores the student ID, course code, component ID, and marks obtained, with getters and a setter for the mark.

### 7. Report.h / Report.cpp
* **Role:** Builds and displays performance reports.
* **Content:**
  * Reads from `Student` and `Course` objects to print a single student's report across their courses, or a class-wide report for a given course.

### 8. SystemController.h / SystemController.cpp
* **Role:** Coordinates the whole system, from loading files to running the menu.
* **Content:**
  * Holds private arrays of `Course` and `Student` pointers (composition).
  * **Loading and saving data (`load...` / `save...` functions):** Reads and writes the four semicolon-separated text files, parsing each line and checking array limits so it never exceeds the fixed capacity.
  * **Searching:** Simple loops to find a course or student by its code or ID.
  * **Managing records:** Functions to add or update courses, students, components, and marks, all driven by user input from the menu.
  * **Reporting:** Calls into `Report` to generate student and class reports.
  * **`showMenu()`:** Runs the main menu loop and dispatches each choice to the relevant function.

### 9. CourseworkManagementSystem.cpp (Program Entry Point)
* **Role:** The starting point of the program.
* **Content:**
  * Creates a single `SystemController` object.
  * Loads `course.txt`, `components.txt`, `student.txt`, and `marks.txt` once at startup.
  * Runs `showMenu()` for the rest of the session.
  * Saves all data back to the four text files once, right before the program exits.

---

## Data File Prerequisites

The program needs its input files to be in the same folder as the executable before it runs. Make sure these four files exist:

* `course.txt` — one course per line (`CourseCode;CourseName;CreditHour`).
* `components.txt` — one component per line (`CourseCode;ComponentID;ComponentName;MaxMarks;Weightage`).
* `student.txt` — one student per line (`StudentID;StudentName`).
* `marks.txt` — one mark record per line (`StudentID;CourseCode;ComponentID;MarksObtained`).

*Note: all four files are also rewritten by the program itself when you exit through the menu, so any courses, components, students, or marks you add or update during the session are saved automatically.*

---

## Compilation and Execution

### Using the Command Line

1. Open a terminal or command prompt inside the project folder where the source files are.
2. Compile the source files into an executable with a standard C++ compiler such as `g++`:
   ```bash
   g++ -c Person.cpp Student.cpp Component.cpp Assignment.cpp Quiz.cpp Project.cpp FinalExam.cpp Course.cpp Mark.cpp Report.cpp SystemController.cpp CourseworkManagementSystem.cpp
   g++ Person.o Student.o Component.o Assignment.o Quiz.o Project.o FinalExam.o Course.o Mark.o Report.o SystemController.o CourseworkManagementSystem.o -o CourseworkManagementSystem
   ```
3. Run the program:
   ```bash
   ./CourseworkManagementSystem      # Linux / macOS
   CourseworkManagementSystem.exe    # Windows
   ```

---

## How It Works

When the program starts, it loads the existing data and shows the main menu:

```
------ Coursework Management System ------
1. List Courses
2. List Students
3. Manage Course
4. Manage Student
5. Define Component
6. Enter/Update Mark
7. Generate Student Report
8. Generate Class Report
0. Exit
```

Notes:

* A component's weighted score is calculated by scaling the mark obtained against its maximum marks and its weightage.
* A student's overall mark for a course is the sum of the weighted scores of every component they have attempted in that course, converted into a letter grade and grade point on a fixed scale (for example, 85 and above is an A+ at 4.00).
* Courses, students, components per course, and mark records per student are each limited to **50 entries**.
* Records are only written back to file when you choose **option 0** to exit, so always exit through the menu rather than closing the window directly.

