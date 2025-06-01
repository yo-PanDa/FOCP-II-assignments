#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
using namespace std;

// =====================
// Exception Classes
// =====================
class UniversitySystemException : public exception {
    string message;
public:
    UniversitySystemException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class EnrollmentException : public UniversitySystemException {
public:
    EnrollmentException(string msg) : UniversitySystemException("Enrollment Error: " + msg) {}
};

class GradeException : public UniversitySystemException {
public:
    GradeException(string msg) : UniversitySystemException("Grade Error: " + msg) {}
};

// =====================
// Person Hierarchy
// =====================
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
};

class Student : public Person {
protected:
    string program;
    double gpa;
    vector<string> courses;
public:
    Student(string n, int a, string i, string prog, double g)
        : Person(n, a, i), program(prog), gpa(g) {
        if (g < 0.0 || g > 4.0) throw GradeException("GPA must be between 0.0 and 4.0");
    }
    void enrollCourse(string course) { courses.push_back(course); }
    void displayDetails() const override {
        Person::displayDetails();
        cout << "Program: " << program << ", GPA: " << gpa << "\nCourses: ";
        for (auto& c : courses) cout << c << " ";
        cout << endl;
    }
    double calculatePayment() const override { return 5000.0; }
};

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
    string getName() const { return name; }
};

// =====================
// GradeBook
// =====================
class GradeBook {
    map<string, double> grades; // student ID -> grade
public:
    void addGrade(string studentId, double grade) {
        if (grade < 0.0 || grade > 100.0) throw GradeException("Invalid grade entry");
        grades[studentId] = grade;
    }
    void report() const {
        double total = 0, maxGrade = 0;
        for (auto& g : grades) {
            total += g.second;
            maxGrade = max(maxGrade, g.second);
            if (g.second < 50) cout << "Failing: " << g.first << " (" << g.second << ")\n";
        }
        cout << "Average: " << (grades.empty() ? 0 : total / grades.size()) << ", Highest: " << maxGrade << endl;
    }
};

// =====================
// EnrollmentManager
// =====================
class EnrollmentManager {
    map<string, vector<string>> courseEnrollments;
    const int maxCapacity = 2;
public:
    void enroll(string courseCode, string studentId) {
        if (courseEnrollments[courseCode].size() >= maxCapacity)
            throw EnrollmentException("Course " + courseCode + " is full");
        courseEnrollments[courseCode].push_back(studentId);
    }
    void report() const {
        for (auto& entry : courseEnrollments) {
            cout << "Course: " << entry.first << ", Enrolled Students: ";
            for (auto& sid : entry.second) cout << sid << " ";
            cout << endl;
        }
    }
};

// =====================
// Course and Classroom
// =====================
class Course {
    string code, title;
    shared_ptr<Professor> instructor;
    GradeBook gradebook;
public:
    Course(string c, string t, shared_ptr<Professor> prof) : code(c), title(t), instructor(prof) {}
    string getCode() const { return code; }
    void displayCourse() const {
        cout << "\nCourse: " << title << " (" << code << ")\nInstructor: " << instructor->getName() << endl;
    }
    GradeBook& getGradeBook() { return gradebook; }
};

class Classroom {
    string roomNumber;
public:
    Classroom() : roomNumber("Unknown") {}
    Classroom(string rn) : roomNumber(rn) {}
    void displayClassroom() const { cout << "Classroom: " << roomNumber << endl; }
    string getRoomNumber() const { return roomNumber; } // ✅ Added getter for map key
};

// =====================
// UniversitySystem
// =====================
class UniversitySystem {
    map<string, shared_ptr<Student>> students;
    map<string, shared_ptr<Professor>> professors;
    map<string, shared_ptr<Course>> courses;
    map<string, shared_ptr<Classroom>> classrooms;
    EnrollmentManager enrollment;

public:
    void addStudent(shared_ptr<Student> student) { students[student->getId()] = student; }
    void addProfessor(shared_ptr<Professor> prof) { professors[prof->getId()] = prof; }
    void addCourse(shared_ptr<Course> course) { courses[course->getCode()] = course; }
    void addClassroom(shared_ptr<Classroom> room) {
        classrooms[room->getRoomNumber()] = room; // ✅ Fixed here
    }

    void enrollStudent(string courseCode, string studentId) {
        if (!students.count(studentId)) throw EnrollmentException("Student not found");
        if (!courses.count(courseCode)) throw EnrollmentException("Course not found");
        enrollment.enroll(courseCode, studentId);
        students[studentId]->enrollCourse(courseCode);
        cout << "Student enrolled successfully!\n";
    }

    void enterGrade(string courseCode, string studentId, double grade) {
        if (!courses.count(courseCode)) throw GradeException("Course not found");
        courses[courseCode]->getGradeBook().addGrade(studentId, grade);
        cout << "Grade entered successfully!\n";
    }

    void showReports() {
        cout << "\n=== Enrollment Report ===\n";
        enrollment.report();
        cout << "\n=== Courses Report ===\n";
        for (auto& c : courses) c.second->displayCourse();
    }
};

// =====================
// Main Menu
// =====================
int main() {
    UniversitySystem uni;

    try {
        // Sample data
        auto prof1 = make_shared<Professor>("Dr. Smith", 50, "P001", "Computer Science");
        auto student1 = make_shared<Student>("Alice", 20, "S001", "CS", 3.8);
        auto course1 = make_shared<Course>("CS101", "Intro to CS", prof1);
        auto room101 = make_shared<Classroom>("Room 101");

        uni.addProfessor(prof1);
        uni.addStudent(student1);
        uni.addCourse(course1);
        uni.addClassroom(room101);

        int choice;
        do {
            cout << "\n--- University Management System ---\n";
            cout << "1. Enroll Student in Course\n";
            cout << "2. Enter Student Grade\n";
            cout << "3. Show Reports\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                string courseCode, studentId;
                cout << "Enter Course Code: ";
                cin >> courseCode;
                cout << "Enter Student ID: ";
                cin >> studentId;
                uni.enrollStudent(courseCode, studentId);
            }
            else if (choice == 2) {
                string courseCode, studentId;
                double grade;
                cout << "Enter Course Code: ";
                cin >> courseCode;
                cout << "Enter Student ID: ";
                cin >> studentId;
                cout << "Enter Grade: ";
                cin >> grade;
                uni.enterGrade(courseCode, studentId, grade);
            }
            else if (choice == 3) {
                uni.showReports();
            }
        } while (choice != 0);

    } catch (UniversitySystemException& e) {
        cerr << e.what() << endl;
    } catch (exception& e) {
        cerr << "System Error: " << e.what() << endl;
    }

    return 0;
}