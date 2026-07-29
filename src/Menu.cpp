#include <iostream>
#include <limits>

#include "Menu.h"
#include "Admin.h"
#include "Faculty.h"
#include "Student.h"
#include "DatabaseConnection.h"
#include "StudentManager.h"
#include "FacultyManager.h"

using namespace std;

void Menu::showMainMenu(){
    DatabaseConnection database;

    if (!database.connect()){
        cout << "Unable to start the system because database connection failed."<< endl;
        return;
    }
    
    Admin admin(3,"System Admin","admin@iitgoa.ac.in","admin123");

    Faculty faculty(2,"Dr. Kalpesh Haria","haria@iitgoa.ac.in","faculty123",201,"FAC2026001",1,"Assistant Professor");

    Student student(1,"Harsh Bhavsar","2403310@iitgoa.ac.in","password123",101,"2403310",1,4,2026);

    int choice = 0;

    while (choice != 4)
    {
        cout << "\n===== ACADEMIC MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. Faculty Login" << endl;
        cout << "3. Student Login" << endl;
        cout << "4. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1){
            cout << "\nAdmin selected." << endl;
            showAdminMenu(database.getSession());
        }
        else if (choice == 2){
            cout << "\nFaculty selected." << endl;
            faculty.displayDashboard();
        }
        else if (choice == 3){
            cout << "\nStudent selected." << endl;
            student.displayDashboard();
        }
        else if (choice == 4){
            cout << "\nExiting the system..." << endl;
        }
        else{
            cout << "\nInvalid choice. Enter a number from 1 to 4." << endl;
        }
    }
}

void Menu::showAdminMenu(mysqlx::Session* session){
    int choice = 0;
    while (choice != 8){
        cout << "\n========== ADMIN MENU ==========" << endl;
        cout << "1. Manage Students" << endl;
        cout << "2. Manage Faculty" << endl;
        cout << "3. Manage Departments" << endl;
        cout << "4. Manage Courses" << endl;
        cout << "5. Manage Semester Offerings" << endl;
        cout << "6. Manage Enrollments" << endl;
        cout << "7. Manage Marks" << endl;
        cout << "8. Back to Main Menu" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1){
            StudentManager studentManager(session);
            studentManager.showStudentManagementMenu();
        }
        else if (choice == 2){
                FacultyManager facultyManager(session);
                facultyManager.showFacultyManagementMenu();
        }
        else if (choice == 3){
            cout << "\nDepartment management is not implemented yet." << endl;
        }
        else if (choice == 4){
            cout << "\nCourse management is not implemented yet." << endl;
        }
        else if (choice == 5){
            cout << "\nSemester offering management is not implemented yet." << endl;
        }
        else if (choice == 6){
            cout << "\nEnrollment management is not implemented yet." << endl;
        }
        else if (choice == 7){
            cout << "\nMarks management is not implemented yet." << endl;
        }
        else if (choice == 8){
            cout << "\nReturning to main menu..." << endl;
        }
        else{
            cout << "\nInvalid choice. Enter a number from 1 to 8." << endl;
        }
    }
}

