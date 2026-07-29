#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include <mysqlx/xdevapi.h>
#include <string>
using namespace std;

class StudentManager{
private:
    mysqlx::Session* session;

    void updateStudentName(const string& rollNumber);
    void updateStudentEmail(const string& rollNumber);
    void updateStudentDepartment(const string& rollNumber);
    void updateStudentSemester(const string& rollNumber);
    void updateStudentAdmissionYear(const string& rollNumber);

public:
    StudentManager(mysqlx::Session* databaseSession);

    void showStudentManagementMenu();

    void addStudent();
    void viewAllStudents();
    void searchStudent();
    void updateStudent();
    void deactivateStudent();
};

#endif