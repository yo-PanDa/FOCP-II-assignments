#include <iostream>
#include <vector>
#include <map>
#include <memory>
using namespace std;

// ========================
// Simplified Base Class
// ========================
class Person {
protected:
    string name, id, contact;
    int age;

public:
    Person(string n, int a, string i, string c) : name(n), id(i), contact(c), age(a) {
        if (n.empty() || a <= 0 || a > 120) throw invalid_argument("Invalid name or age");
    }
    virtual ~Person() {}

    virtual void displayDetails() const {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << id << ", Contact: " << contact << endl;
    }

    virtual double calculatePayment() const { return 0.0; }

    string getId() const { return id; }
    string getName() const { return name; }
};

// ========================
// Simplified Student Class
// ========================
class Student : public Person {
    string enrollmentDate, program;
    double gpa;

public:
    Student(string n, int a, string i, string c, string ed, string prog, double g)
        : Person(n, a, i, c), enrollmentDate(ed), program(prog), gpa(g) {
        if (g < 0.0 || g > 4.0) throw invalid_argument("Invalid GPA");
    }

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Program: " << program << ", Enrollment: " << enrollmentDate << ", GPA: " << gpa << endl;
    }

    double calculatePayment() const override { return 5000.0; }
};

// ========================
// Simplified Professor Class
// ========================
class Professor : public Person {
    string department, specialization, hireDate;

public:
    Professor(string n, int a, string i, string c, string d, string s, string h)
        : Person(n, a, i, c), department(d), specialization(s), hireDate(h) {}

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Dept: " << department << ", Specialization: " << specialization << ", Hire Date: " << hireDate << endl;
    }

    double calculatePayment() const override { return 70000.0; }
};

// ========================
// Simplified Course Class
// ========================
class Course {
    string code, title, desc;
    int credits;

public:
    Course(string c, string t, int cr, string d) : code(c), title(t), desc(d), credits(cr) {
        if (cr <= 0) throw invalid_argument("Invalid credits");
    }

    void displayCourse() const {
        cout << "Course: " << title << " (" << code << "), Credits: " << credits << ", " << desc << endl;
    }

    string getCode() const { return code; }
};

// ========================
// Simplified Department Class
// ========================
class Department {
    string name, location;
    double budget;

public:
    Department(string n, string l, double b) : name(n), location(l), budget(b) {}

    void displayDepartment() const {
        cout << "Department: " << name << ", Location: " << location << ", Budget: $" << budget << endl;
    }
};

// ========================
// GradeBook Class
// ========================
class GradeBook {
    map<string, double> grades;

public:
    void addGrade(string id, double grade) {
        if (grade < 0 || grade > 100) throw invalid_argument("Invalid grade");
        grades[id] = grade;
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

// ========================
// EnrollmentManager Class
// ========================
class EnrollmentManager {
    map<string, vector<string>> enrollments;

public:
    void enroll(string course, string studentId) { enrollments[course].push_back(studentId); }

    void report() const {
        for (const auto& entry : enrollments) {
            cout << "Course: " << entry.first << " | Students: ";
            for (const auto& s : entry.second) cout << s << " ";
            cout << endl;
        }
    }
};

// ========================
// Main Program
// ========================
int main() {
    vector<Student> students;
    vector<Professor> professors;
    vector<Course> courses;
    vector<Department> departments;
    GradeBook gradebook;
    EnrollmentManager enrollment;

    int choice;

    do {
        cout << "\n--- University Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Add Professor\n";
        cout << "3. Add Course\n";
        cout << "4. Add Department\n";
        cout << "5. Enroll Student in Course\n";
        cout << "6. Add Grade\n";
        cout << "7. Show Reports\n";
        cout << "8. Show All Data\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            if (choice == 1) {
                string name, id, contact, enrollmentDate, program;
                int age;
                double gpa;
                cout << "Enter name: "; cin.ignore(); getline(cin, name);
                cout << "Enter age: "; cin >> age;
                cout << "Enter ID: "; cin >> id;
                cout << "Enter contact: "; cin >> contact;
                cout << "Enter enrollment date: "; cin >> enrollmentDate;
                cout << "Enter program: "; cin >> program;
                cout << "Enter GPA: "; cin >> gpa;
                students.emplace_back(name, age, id, contact, enrollmentDate, program, gpa);
            }
            else if (choice == 2) {
                string name, id, contact, department, specialization, hireDate;
                int age;
                cout << "Enter name: "; cin.ignore(); getline(cin, name);
                cout << "Enter age: "; cin >> age;
                cout << "Enter ID: "; cin >> id;
                cout << "Enter contact: "; cin >> contact;
                cout << "Enter department: "; cin >> department;
                cout << "Enter specialization: "; cin >> specialization;
                cout << "Enter hire date: "; cin >> hireDate;
                professors.emplace_back(name, age, id, contact, department, specialization, hireDate);
            }
            else if (choice == 3) {
                string code, title, desc;
                int credits;
                cout << "Enter course code: "; cin >> code;
                cout << "Enter title: "; cin.ignore(); getline(cin, title);
                cout << "Enter credits: "; cin >> credits;
                cout << "Enter description: "; cin.ignore(); getline(cin, desc);
                courses.emplace_back(code, title, credits, desc);
            }
            else if (choice == 4) {
                string name, location;
                double budget;
                cout << "Enter department name: "; cin.ignore(); getline(cin, name);
                cout << "Enter location: "; cin >> location;
                cout << "Enter budget: "; cin >> budget;
                departments.emplace_back(name, location, budget);
            }
            else if (choice == 5) {
                if (courses.empty() || students.empty()) {
                    cout << "No courses or students available.\n";
                    continue;
                }
                cout << "Available courses:\n";
                for (size_t i = 0; i < courses.size(); ++i)
                    cout << i + 1 << ". " << courses[i].getCode() << endl;
                int courseIndex;
                cout << "Choose course number: "; cin >> courseIndex;

                cout << "Available students:\n";
                for (size_t i = 0; i < students.size(); ++i)
                    cout << i + 1 << ". " << students[i].getId() << endl;
                int studentIndex;
                cout << "Choose student number: "; cin >> studentIndex;

                enrollment.enroll(courses[courseIndex - 1].getCode(), students[studentIndex - 1].getId());
                cout << "Student enrolled!\n";
            }
            else if (choice == 6) {
                if (students.empty()) {
                    cout << "No students available.\n";
                    continue;
                }
                cout << "Available students:\n";
                for (size_t i = 0; i < students.size(); ++i)
                    cout << i + 1 << ". " << students[i].getId() << endl;
                int studentIndex;
                cout << "Choose student number: "; cin >> studentIndex;

                double grade;
                cout << "Enter grade: "; cin >> grade;
                gradebook.addGrade(students[studentIndex - 1].getId(), grade);
                cout << "Grade added!\n";
            }
            else if (choice == 7) {
                cout << "\n--- Enrollment Report ---\n";
                enrollment.report();
                cout << "\n--- Grade Report ---\n";
                gradebook.report();
            }
            else if (choice == 8) {
                cout << "\n--- All Students ---\n";
                for (const auto& s : students) s.displayDetails();
                cout << "\n--- All Professors ---\n";
                for (const auto& p : professors) p.displayDetails();
                cout << "\n--- All Courses ---\n";
                for (const auto& c : courses) c.displayCourse();
                cout << "\n--- All Departments ---\n";
                for (const auto& d : departments) d.displayDepartment();
            }

        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }

    } while (choice != 0);

    cout << "Exiting University Management System.\n";
    return 0;
}