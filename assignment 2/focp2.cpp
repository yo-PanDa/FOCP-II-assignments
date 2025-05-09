#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int rollNumber;
    float CGPA;
    vector<string> courses;

public:
    Student() {
        name = "";
        rollNumber = 0;
        CGPA = 0.0;
    }

    Student(string n, int r, float c) {
        name = n;
        rollNumber = r;
        CGPA = (c >= 0.0 && c <= 4.0) ? c : 0.0;
    }

    Student(const Student& s) {
        name = s.name;
        rollNumber = s.rollNumber;
        CGPA = s.CGPA;
        courses = s.courses;
    }

    ~Student() {
        cout << "Destroying student: " << name << endl;
    }
};
class Student {
    private:
        string name;
        int rollNumber;
        float CGPA;
        vector<string> courses;
    
    public:

        void addCourse(string course) {
            if (!course.empty())
                courses.push_back(course);
            else
                cout << "Invalid course name.\n";
        }

        void updateCGPA(float newCGPA) {
            if (newCGPA >= 0.0 && newCGPA <= 4.0)
                CGPA = newCGPA;
            else
                cout << "Invalid CGPA. Must be between 0.0 and 4.0.\n";
        }

        void displayInfo() const {
            cout << "Name: " << name << "\nRoll Number: " << rollNumber
                 << "\nCGPA: " << CGPA << "\nCourses: ";
            for (const auto& c : courses) cout << c << " ";
            cout << endl;
        }

        int getRollNumber() const { return rollNumber; }
    };
    class StudentManagementSystem {
        private:
            vector<Student> students;
        
        public:
            void addStudent(const Student& s) {
                students.push_back(s);
            }
        
            void searchStudentByRoll(int roll) const {
                for (const auto& s : students) {
                    if (s.getRollNumber() == roll) {
                        s.displayInfo();
                        return;
                    }
                }
                cout << "Student not found.\n";
            }
        
            void displayAllStudents() const {
                for (const auto& s : students) {
                    s.displayInfo();
                }
            }
        };

        int main() {
            StudentManagementSystem sms;
            Student s1("joy", 1, 3.7);
            s1.addCourse("focp");
            s1.addCourse("chemistry");
        
            Student s2("left out", 2, 3.9);
            s2.addCourse("chemistry");
        
            sms.addStudent(s1);
            sms.addStudent(s2);
        
            sms.displayAllStudents();
            sms.searchStudentByRoll(1);
        
            return 0;
        }