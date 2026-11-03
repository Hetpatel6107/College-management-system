#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

class Student;

// Base class
class College {
protected:
    string name;
    int age, id;

public:
    virtual void input() {
        cout << "Enter ID: ";
        cin >> id;

        cout << "Enter Name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
    }

    virtual void display() {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(8) << age;
    }

    virtual void searchStudent(Student s[], int count);
    virtual void sortStudents(Student s[], int count);
    virtual void updateStudent(Student s[], int &count);
    virtual void deleteStudent(Student s[], int &count);
    virtual void calculateResult(Student s[], int count);

    int getID() {
        return id;
    }
};

// Student class
class Student : public College {
    string branch;
    int semester;
    float cpi;

public:
    void input() {
        College::input();

        cout << "Enter Branch: ";
        cin >> branch;

        cout << "Enter Semester: ";
        cin >> semester;

        cout << "Enter CPI (0-10): ";
        cin >> cpi;

        if (cpi < 0 || cpi > 10)
            throw "Invalid CPI! Enter CPI between 0 and 10.";
    }

    float getCPI() {
        return cpi;
    }

    string getName() {
        return name;
    }

    string getGrade() {
        if (cpi >= 9) return "A+";
        else if (cpi >= 8) return "A";
        else if (cpi >= 7) return "B";
        else if (cpi >= 6) return "C";
        else if (cpi >= 5) return "D";
        else if (cpi >= 4) return "E";
        else return "F";
    }

    void display() {
        College::display();

        cout << left << setw(12) << branch
             << setw(10) << semester
             << setw(10) << fixed << setprecision(2) << cpi
             << setw(8) << getGrade() << endl;
    }

    void saveToFile() {
        ofstream fout("Student.txt", ios::app);

        fout << id << '\t' << name << '\t'
             << age << '\t' << branch << '\t'
             << semester << '\t' << cpi << '\t'
             << getGrade() << endl;

        fout.close();
    }

    // Rewrite file with current student records
    void updateFile(Student s[], int count) {
        ofstream fout("Student.txt");

        for (int i = 0; i < count; i++) {
            fout << s[i].id << '\t'
                 << s[i].name << '\t'
                 << s[i].age << '\t'
                 << s[i].branch << '\t'
                 << s[i].semester << '\t'
                 << s[i].cpi << '\t'
                 << s[i].getGrade() << endl;
        }

        fout.close();
    }

    // Search student by ID
    void searchStudent(Student s[], int count) {
        int searchID;
        bool found = false;

        cout << "Enter Student ID: ";
        cin >> searchID;

        for (int i = 0; i < count; i++) {
            if (s[i].getID() == searchID) {
                cout << "\nStudent Found:\n";

                cout << left
                     << setw(10) << "ID"
                     << setw(20) << "Name"
                     << setw(8) << "Age"
                     << setw(12) << "Branch"
                     << setw(10) << "Semester"
                     << setw(10) << "CPI"
                     << setw(8) << "Grade" << endl;

                cout << string(78, '-') << endl;

                s[i].display();
                found = true;
                break;
            }
        }

        if (found == false)
            cout << "Student not found!\n";
    }

    // Sort students by CPI
    void sortStudents(Student s[], int count) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (s[j].getCPI() < s[j + 1].getCPI()) {
                    Student temp = s[j];
                    s[j] = s[j + 1];
                    s[j + 1] = temp;
                }
            }
        }

        updateFile(s, count);

        cout << "\nStudents sorted by CPI (highest first):\n";

        cout << left
             << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(8) << "Age"
             << setw(12) << "Branch"
             << setw(10) << "Semester"
             << setw(10) << "CPI"
             << setw(8) << "Grade" << endl;

        cout << string(78, '-') << endl;

        for (int i = 0; i < count; i++)
            s[i].display();
    }

    // Update student
    void updateStudent(Student s[], int &count) {
        int searchID;
        bool found = false;

        cout << "Enter Student ID to update: ";
        cin >> searchID;

        for (int i = 0; i < count; i++) {
            if (s[i].getID() == searchID) {
                Student temp;

                cout << "Enter new details:\n";
                temp.input();

                s[i] = temp;
                updateFile(s, count);

                cout << "Student updated in memory and file!\n";
                found = true;
                break;
            }
        }

        if (found == false)
            cout << "Student not found!\n";
    }

    // Delete student
    void deleteStudent(Student s[], int &count) {
        int searchID;
        bool found = false;

        cout << "Enter Student ID to delete: ";
        cin >> searchID;

        for (int i = 0; i < count; i++) {
            if (s[i].getID() == searchID) {
                for (int j = i; j < count - 1; j++)
                    s[j] = s[j + 1];

                count--;
                updateFile(s, count);

                cout << "Student deleted from memory and file!\n";
                found = true;
                break;
            }
        }

        if (found == false)
            cout << "Student not found!\n";
    }

    // Calculate grade and result
    void calculateResult(Student s[], int count) {
        int searchID;
        bool found = false;

        cout << "Enter Student ID: ";
        cin >> searchID;

        for (int i = 0; i < count; i++) {
            if (s[i].getID() == searchID) {
                cout << "Name: " << s[i].getName() << endl;
                cout << "CPI: " << s[i].getCPI() << endl;
                cout << "Grade: " << s[i].getGrade() << endl;

                if (s[i].getCPI() >= 4)
                    cout << "Result: PASS\n";
                else
                    cout << "Result: FAIL\n";

                found = true;
                break;
            }
        }

        if (found == false)
            cout << "Student not found!\n";
    }
};

// Base class function definitions
void College::searchStudent(Student s[], int count) {}
void College::sortStudents(Student s[], int count) {}
void College::updateStudent(Student s[], int &count) {}
void College::deleteStudent(Student s[], int &count) {}
void College::calculateResult(Student s[], int count) {}

// Faculty class
class Faculty : public College {
protected:
    string branch, course;
    double basicSalary;

public:
    void input() {
        College::input();

        cout << "Enter Branch: ";
        cin >> branch;

        cout << "Enter Course: ";
        cin >> course;

        cout << "Enter Basic Salary: ";
        cin >> basicSalary;
    }

    virtual double getAllowance() {
        return 0;
    }

    void display() {
        College::display();

        cout << left << setw(12) << branch
             << setw(15) << course
             << setw(12) << fixed << setprecision(2) << basicSalary
             << setw(12) << getAllowance()
             << setw(12) << basicSalary + getAllowance()
             << endl;
    }

    void saveToFile() {
        ofstream fout("faculty.txt", ios::app);

        fout << id << '\t' << name << '\t'
             << age << '\t' << branch << '\t'
             << course << '\t' << basicSalary << '\t'
             << getAllowance() << '\t'
             << basicSalary + getAllowance() << endl;

        fout.close();
    }
};

// Main Professor
class MainProfessor : public Faculty {
public:
    double getAllowance() {
        return basicSalary * 0.40;
    }
};

// Assistant Professor
class AssistantProfessor : public Faculty {
public:
    double getAllowance() {
        return basicSalary * 0.20;
    }
};

int main() {
    Student s[100];
    MainProfessor mp[100];
    AssistantProfessor ap[100];

    College *ptr;

    int studentCount = 0;
    int mainCount = 0;
    int assistantCount = 0;
    int choice;

    do {
        cout << "\n===== COLLEGE MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Calculate Grade and Result\n";
        cout << "7. Sort Students by CPI\n";
        cout << "8. Add Main Professor\n";
        cout << "9. Add Assistant Professor\n";
        cout << "10. Display Main Professors\n";
        cout << "11. Display Assistant Professors\n";
        cout << "12. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1:
                    if (studentCount < 100) {
                        ptr = &s[studentCount];
                        ptr->input();

                        s[studentCount].saveToFile();
                        studentCount++;

                        cout << "Student added successfully!\n";
                    } else {
                        cout << "Student limit reached!\n";
                    }
                    break;

                case 2:
                    if (studentCount == 0) {
                        cout << "No students found!\n";
                        break;
                    }

                    cout << left
                         << setw(10) << "ID"
                         << setw(20) << "Name"
                         << setw(8) << "Age"
                         << setw(12) << "Branch"
                         << setw(10) << "Semester"
                         << setw(10) << "CPI"
                         << setw(8) << "Grade" << endl;

                    cout << string(78, '-') << endl;

                    for (int i = 0; i < studentCount; i++) {
                        ptr = &s[i];
                        ptr->display();
                    }
                    break;

                case 3:
                    if (studentCount > 0) {
                        ptr = &s[0];
                        ptr->searchStudent(s, studentCount);
                    } else {
                        cout << "No students found!\n";
                    }
                    break;

                case 4:
                    if (studentCount > 0) {
                        ptr = &s[0];
                        ptr->updateStudent(s, studentCount);
                    } else {
                        cout << "No students found!\n";
                    }
                    break;

                case 5:
                    if (studentCount > 0) {
                        ptr = &s[0];
                        ptr->deleteStudent(s, studentCount);
                    } else {
                        cout << "No students found!\n";
                    }
                    break;

                case 6:
                    if (studentCount > 0) {
                        ptr = &s[0];
                        ptr->calculateResult(s, studentCount);
                    } else {
                        cout << "No students found!\n";
                    }
                    break;

                case 7:
                    if (studentCount > 0) {
                        ptr = &s[0];
                        ptr->sortStudents(s, studentCount);
                    } else {
                        cout << "No students to sort!\n";
                    }
                    break;

                case 8:
                    if (mainCount < 100) {
                        ptr = &mp[mainCount];
                        ptr->input();

                        mp[mainCount].saveToFile();
                        mainCount++;

                        cout << "Main Professor added successfully!\n";
                    } else {
                        cout << "Main Professor limit reached!\n";
                    }
                    break;

                case 9:
                    if (assistantCount < 100) {
                        ptr = &ap[assistantCount];
                        ptr->input();

                        ap[assistantCount].saveToFile();
                        assistantCount++;

                        cout << "Assistant Professor added successfully!\n";
                    } else {
                        cout << "Assistant Professor limit reached!\n";
                    }
                    break;

                case 10:
                    if (mainCount == 0) {
                        cout << "No Main Professors found!\n";
                    } else {
                        cout << "\nMain Professor Records:\n";

                        cout << left
                             << setw(10) << "ID"
                             << setw(20) << "Name"
                             << setw(8) << "Age"
                             << setw(12) << "Branch"
                             << setw(15) << "Course"
                             << setw(12) << "Basic Pay"
                             << setw(12) << "Allowance"
                             << setw(12) << "Total Pay" << endl;

                        cout << string(101, '-') << endl;

                        for (int i = 0; i < mainCount; i++) {
                            ptr = &mp[i];
                            ptr->display();
                        }
                    }
                    break;

                case 11:
                    if (assistantCount == 0) {
                        cout << "No Assistant Professors found!\n";
                    } else {
                        cout << "\nAssistant Professor Records:\n";

                        cout << left
                             << setw(10) << "ID"
                             << setw(20) << "Name"
                             << setw(8) << "Age"
                             << setw(12) << "Branch"
                             << setw(15) << "Course"
                             << setw(12) << "Basic Pay"
                             << setw(12) << "Allowance"
                             << setw(12) << "Total Pay" << endl;

                        cout << string(101, '-') << endl;

                        for (int i = 0; i < assistantCount; i++) {
                            ptr = &ap[i];
                            ptr->display();
                        }
                    }
                    break;

                case 12:
                    cout << "Thank you! Exiting...\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
            }
        }
        catch (const char* msg) {
            cout << "Exception: " << msg << endl;
        }

    } while (choice != 12);

    return 0;
}
