#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"
#include <string>

using namespace std;

class Faculty : public User
{
protected:
    int facultyId;
    string employeeCode;
    int departmentId;
    string designation;

public:
    Faculty();

    Faculty(
        int userId,
        string name,
        string email,
        string password,
        int facultyId,
        string employeeCode,
        int departmentId,
        string designation
    );

    // Setters
    void setFacultyId(int facultyId);
    void setEmployeeCode(string employeeCode);
    void setDepartmentId(int departmentId);
    void setDesignation(string designation);

    // Getters
    int getFacultyId();
    string getEmployeeCode();
    int getDepartmentId();
    string getDesignation();

    void displayDashboard() override;

    ~Faculty() override;
};

#endif