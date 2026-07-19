#ifndef STUDENT_H
#define STUDENT_H
#include "User.h"
#include <string>
using namespace std;

class Student : public User{
private:
    int studentId;
    string rollNumber;
    int departmentId;
    int currentSemester;
    int admissionYear;

public:
    Student();

    Student(int userId, string name, string email, string password, int studentId, string rollNumber, int departmentId, int currentSemester, int admissionYear);

    // Setters
    void setStudentId(int StudentId);
    void setRollNumber(string rollNumber);
    void setDepartmentId(int departmentId);
    void setCurrentSemester(int currentSemester);
    void setAdmissionYear(int admissionYear);

    // Getters
    int getStudentId();
    string getRollNumber();
    int getDepartmentId();
    int getCurrentSemester();
    int getAdmissionYear();

    void displayDashboard() override;

    ~Student() override;
};
#endif