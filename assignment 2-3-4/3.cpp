#include <iostream>
#include <vector>
#include <map>
#include <memory>
using namespace std;

// ========================
// Base Class: Person
// ========================
class Person {
protected:
    string name, id;
    int age;

public:
    Person(string n, int a, string i) : name(n), id(i), age(a) {}
    virtual ~Person() {}

    virtual void displayDetails() const {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << id << endl;
    }

    virtual double calculatePayment() const { return 0.0; }

    string getId() const { return id; }
    string getName() const { return name; }
};

// ========================
// Student Hierarchy
// ========================
class Student : public Person {
protected:
    string program;
    double gpa;
    vector<string> courses;

public:
    Student(string n, int a, string i, string prog, double g)
        : Person(n, a, i), program(prog), gpa(g) {}

    void enrollCourse(string course) { courses.push_back(course); }

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Program: " << program << ", GPA: " << gpa << "\nCourses: ";
        for (auto& c : courses) cout << c << " ";
        cout << endl;
    }

    double calculatePayment() const override { return 5000.0; }
};

// ========================
// Professor Hierarchy
// ========================
class Professor : public Person {
protected:
    string department;

public:
    Professor(string n, int a, string i, string dept) : Person(n, a, i), department(dept) {}

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Department: " << department << endl;
    }

    double calculatePayment() const override { return 80000.0; }

    string getDepartment() const { return department; }
};

// ========================
// Department (Composition)
// ========================
class Department {
    string name;
    vector<shared_ptr<Professor>> professors;

public:
    Department(string n) : name(n) {}

    void addProfessor(shared_ptr<Professor> prof) { professors.push_back(prof); }

    void displayDepartment() const {
        cout << "\nDepartment: " << name << "\nProfessors:\n";
        for (auto& p : professors) p->displayDetails();
    }

    string getName() const { return name; }
};

// ========================
// Course (Aggregation)
// ========================
class Course {
    string code, title;
    shared_ptr<Professor> instructor;

public:
    Course(string c, string t, shared_ptr<Professor> prof) : code(c), title(t), instructor(prof) {}

    void displayCourse() const {
        cout << "\nCourse: " << title << " (" << code << ")\nInstructor: " << instructor->getName() << endl;
    }

    string getCode() const { return code; }
};

// ========================
// Classroom & Schedule
// ========================
class Classroom {
    string roomNumber;

public:
    Classroom() : roomNumber("Unknown") {}
    Classroom(string rn) : roomNumber(rn) {}

    void displayClassroom() const { cout << "Classroom: " << roomNumber << endl; }
    string getRoomNumber() const { return roomNumber; }
};

class Schedule {
    map<string, shared_ptr<Classroom>> timetable;

public:
    void addSchedule(string courseCode, shared_ptr<Classroom> room) {
        timetable[courseCode] = room;
    }

    void displaySchedule() const {
        for (auto& entry : timetable) {
            cout << "Course: " << entry.first << " in ";
            entry.second->displayClassroom();
        }
    }
};

// ========================
// University Class
// ========================
class University {
    vector<Department> departments;
    vector<shared_ptr<Student>> students;
    vector<shared_ptr<Professor>> professors;
    vector<shared_ptr<Course>> courses;
    vector<shared_ptr<Classroom>> classrooms;
    Schedule schedule;

public:
    void addDepartment() {
        string name;
        cout << "Enter department name: ";
        cin.ignore();
        getline(cin, name);
        Department dept(name);

        if (!professors.empty()) {
            cout << "Assign professors to this department (enter indexes, -1 to stop):\n";
            for (size_t i = 0; i < professors.size(); ++i)
                cout << i + 1 << ". " << professors[i]->getName() << " (" << professors[i]->getDepartment() << ")\n";

            int profChoice;
            while (cin >> profChoice && profChoice != -1) {
                if (profChoice >= 1 && profChoice <= professors.size())
                    dept.addProfessor(professors[profChoice - 1]);
                else
                    cout << "Invalid choice.\n";
            }
        }

        departments.push_back(dept);
    }

    void addProfessor() {
        string name, id, dept;
        int age;
        cout << "Enter professor name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter age: "; cin >> age;
        cout << "Enter ID: "; cin >> id;
        cout << "Enter department: "; cin.ignore(); getline(cin, dept);

        professors.push_back(make_shared<Professor>(name, age, id, dept));
    }

    void addStudent() {
        string name, id, program;
        int age;
        double gpa;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter age: "; cin >> age;
        cout << "Enter ID: "; cin >> id;
        cout << "Enter program: "; cin >> program;
        cout << "Enter GPA: "; cin >> gpa;

        students.push_back(make_shared<Student>(name, age, id, program, gpa));
    }

    void addCourse() {
        if (professors.empty()) {
            cout << "No professors available. Add professor first.\n";
            return;
        }

        string code, title;
        cout << "Enter course code: ";
        cin >> code;
        cout << "Enter course title: ";
        cin.ignore();
        getline(cin, title);

        cout << "Select instructor:\n";
        for (size_t i = 0; i < professors.size(); ++i)
            cout << i + 1 << ". " << professors[i]->getName() << endl;

        int profChoice;
        cin >> profChoice;
        if (profChoice >= 1 && profChoice <= professors.size()) {
            courses.push_back(make_shared<Course>(code, title, professors[profChoice - 1]));
            cout << "Course added successfully.\n";
        } else {
            cout << "Invalid professor choice.\n";
        }
    }

    void addClassroom() {
        string room;
        cout << "Enter classroom number: ";
        cin >> room;
        classrooms.push_back(make_shared<Classroom>(room));
    }

    void assignClassroomToCourse() {
        if (courses.empty() || classrooms.empty()) {
            cout << "Courses or Classrooms list is empty.\n";
            return;
        }

        cout << "Select course:\n";
        for (size_t i = 0; i < courses.size(); ++i)
            cout << i + 1 << ". " << courses[i]->getCode() << endl;

        int courseChoice;
        cin >> courseChoice;

        cout << "Select classroom:\n";
        for (size_t i = 0; i < classrooms.size(); ++i)
            cout << i + 1 << ". " << classrooms[i]->getRoomNumber() << endl;

        int roomChoice;
        cin >> roomChoice;

        if (courseChoice >= 1 && courseChoice <= courses.size() &&
            roomChoice >= 1 && roomChoice <= classrooms.size()) {
            schedule.addSchedule(courses[courseChoice - 1]->getCode(), classrooms[roomChoice - 1]);
            cout << "Classroom assigned to course.\n";
        } else {
            cout << "Invalid choices.\n";
        }
    }

    void displayAll() const {
        cout << "\n--- University Data ---\n";
        for (const auto& dept : departments) dept.displayDepartment();
        for (const auto& course : courses) course->displayCourse();
        for (const auto& student : students) student->displayDetails();
        for (const auto& room : classrooms) room->displayClassroom();
        schedule.displaySchedule();
    }
};

// ========================
// Main Test Program
// ========================
int main() {
    University uni;
    int choice;

    do {
        cout << "\n--- University Management System ---\n";
        cout << "1. Add Department\n";
        cout << "2. Add Professor\n";
        cout << "3. Add Student\n";
        cout << "4. Add Course\n";
        cout << "5. Add Classroom\n";
        cout << "6. Assign Classroom to Course\n";
        cout << "7. Display All Data\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: uni.addDepartment(); break;
            case 2: uni.addProfessor(); break;
            case 3: uni.addStudent(); break;
            case 4: uni.addCourse(); break;
            case 5: uni.addClassroom(); break;
            case 6: uni.assignClassroomToCourse(); break;
            case 7: uni.displayAll(); break;
            case 0: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}