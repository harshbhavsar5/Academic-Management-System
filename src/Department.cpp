#include "../include/Department.h"
#include <iostream>

using namespace std;

// Default constructor
Department::Department()
{
    departmentId = 0;
    departmentName = "";
    hodName = "";
}

// Parameterized constructor
Department::Department(
    int departmentId,
    string departmentName,
    string hodName
)
{
    this->departmentId = departmentId;
    this->departmentName = departmentName;
    this->hodName = hodName;
}

// Setters
void Department::setDepartmentId(int departmentId)
{
    this->departmentId = departmentId;
}

void Department::setDepartmentName(string departmentName)
{
    this->departmentName = departmentName;
}

void Department::setHodName(string hodName)
{
    this->hodName = hodName;
}

// Getters
int Department::getDepartmentId()
{
    return departmentId;
}

string Department::getDepartmentName()
{
    return departmentName;
}

string Department::getHodName()
{
    return hodName;
}

void Department::displayDepartment()
{
    cout << "\n===== DEPARTMENT DETAILS =====" << endl;
    cout << "Department ID: " << departmentId << endl;
    cout << "Department Name: " << departmentName << endl;
    cout << "HOD Name: " << hodName << endl;
}

Department::~Department()
{
}