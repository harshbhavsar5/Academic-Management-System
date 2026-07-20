#include <iostream>
#include "include/User.h"
#include "include/Student.h"
#include "include/Faculty.h"
#include "include/Admin.h"
#include "include/Department.h"
#include "include/Course.h"
#include "include/SemesterOffering.h"
#include "include/Enrollment.h"
using namespace std;

int main()
{
    int userId = 1;
    string name = "Harsh Bhavsar";
    string email = "2403310@iitgoa.ac.in";
    string password = "harsh123";

    // Creating a User object using the parameterized constructor
    User user1(userId, name, email, password);

    cout << "Academic Management System"<<endl;
    cout << "--------------------------"<<endl;

    cout << "User ID: " << user1.getUserId() << endl;
    cout << "Name: " << user1.getName() << endl;
    cout << "Email: " << user1.getEmail() << endl;
    user1.displayDashboard();

    Student student1(1,"Harsh Bhavsar", "2403310@iitgoa.ac.in","password123",101,"2403310",1,4,2026);
    student1.displayDashboard();

    Faculty faculty1(2,"Dr. Kalpesh Haria","haria@iitgoa.ac.in","faculty123",201,"FAC2026001",1,"Assistant Professor");
    faculty1.displayDashboard();

    Admin admin1(3,"System Admin","admin@iitgoa.ac.in","admin123");
    admin1.displayDashboard();

    User* userPtr;
    cout << "\n--- Runtime Polymorphism Test ---" << endl;

    userPtr = &student1;
    userPtr->displayDashboard();

    userPtr = &faculty1;
    userPtr->displayDashboard();

    userPtr = &admin1;
    userPtr->displayDashboard();

    Department department1(1,"Mathematics and Computing","Dr. Kalpesh Haria");
    department1.displayDepartment();

    Course course1(1,"MA205","Abstract Algebra",4,1,4);
    course1.displayCourse();

    SemesterOffering summerOffering1(1,1,201,4,"2025-2026",40);
    summerOffering1.displayOffering();

    Enrollment enrollment1(1,1,1,"2026-08-1","Enrolled");
    enrollment1.displayEnrollment();
    
    return 0;
}