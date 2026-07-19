#include "../include/Student.h"
#include <iostream>
using namespace std;

// Default constructor
Student::Student(){
    studentId = 0;
    rollNumber = "";
    departmentId = 0;
    currentSemester = 1;
    admissionYear = 0;
}

// Parameterized constructor
Student::Student(int userId, string name, string email, string password, int studentId, string rollNumber, int departmentId, int currentSemester, int admissionYear) : User(userId, name, email, password){
    this->studentId = studentId;
    this->rollNumber = rollNumber;
    this->departmentId = departmentId;
    this->currentSemester = currentSemester;
    this->admissionYear = admissionYear;
}

// Setters
void Student::setStudentId(int studentId){
    this->studentId = studentId;
}

void Student::setRollNumber(string rollNumber){
    this->rollNumber = rollNumber;
}

void Student::setDepartmentId(int departmentId){
    this->departmentId = departmentId;
}

void Student::setCurrentSemester(int currentSemester){
    this->currentSemester = currentSemester;
}

void Student::setAdmissionYear(int admissionYear){
    this->admissionYear = admissionYear;
}

// Getters
int Student::getStudentId(){
    return studentId;
}

string Student::getRollNumber(){
    return rollNumber;
}

int Student::getDepartmentId(){
    return departmentId;
}

int Student::getCurrentSemester(){
    return currentSemester;
}

int Student::getAdmissionYear(){
    return admissionYear;
}

void Student::displayDashboard()
{
    cout << "\n===== STUDENT DASHBOARD =====" << endl;

    cout << "Name: " << getName() << endl;
    cout << "Roll Number: " << rollNumber << endl;
    cout << "Department ID: " << departmentId << endl;
    cout << "Current Semester: " << currentSemester << endl;
    cout << "Admission Year: " << admissionYear << endl;
    cout << "\nAvailable Options:" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. View Enrolled Courses" << endl;
    cout << "3. View Marks" << endl;
    cout << "4. View Result" << endl;
    cout << "5. Logout" << endl;
}

// Destructor
Student::~Student()
{
}