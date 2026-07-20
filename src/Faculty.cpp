#include "../include/Faculty.h"
#include <iostream>

using namespace std;

// Default constructor
Faculty::Faculty() : User()
{
    facultyId = 0;
    employeeCode = "";
    departmentId = 0;
    designation = "";
}

// Parameterized constructor
Faculty::Faculty(int userId,string name,string email,string password,int facultyId,string employeeCode,int departmentId,string designation) : User(userId, name, email, password){
    this->facultyId = facultyId;
    this->employeeCode = employeeCode;
    this->departmentId = departmentId;
    this->designation = designation;
}

// Setters
void Faculty::setFacultyId(int facultyId){
    this->facultyId = facultyId;
}

void Faculty::setEmployeeCode(string employeeCode){
    this->employeeCode = employeeCode;
}

void Faculty::setDepartmentId(int departmentId){
    this->departmentId = departmentId;
}

void Faculty::setDesignation(string designation){
    this->designation = designation;
}

// Getters
int Faculty::getFacultyId(){
    return facultyId;
}

string Faculty::getEmployeeCode(){
    return employeeCode;
}

int Faculty::getDepartmentId(){
    return departmentId;
}

string Faculty::getDesignation(){
    return designation;
}

void Faculty::displayDashboard(){
    cout << "\n===== FACULTY DASHBOARD =====" << endl;

    cout << "Name: " << getName() << endl;
    cout << "Employee Code: " << employeeCode << endl;
    cout << "Department ID: " << departmentId << endl;
    cout << "Designation: " << designation << endl;

    cout << "\nAvailable Options:" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. View Assigned Courses" << endl;
    cout << "3. Enter Marks" << endl;
    cout << "4. Update Marks" << endl;
    cout << "5. View Students" << endl;
    cout << "6. Logout" << endl;
}

Faculty::~Faculty(){
}