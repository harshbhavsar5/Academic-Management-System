#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>

using namespace std;

class Department
{
private:
    int departmentId;
    string departmentName;
    string hodName;

public:
    Department();

    Department(
        int departmentId,
        string departmentName,
        string hodName
    );

    // Setters
    void setDepartmentId(int departmentId);
    void setDepartmentName(string departmentName);
    void setHodName(string hodName);

    // Getters
    int getDepartmentId();
    string getDepartmentName();
    string getHodName();

    void displayDepartment();

    ~Department();
};

#endif