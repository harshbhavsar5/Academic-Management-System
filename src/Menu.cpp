#include <iostream>

#include "Menu.h"
#include "Admin.h"
#include "Faculty.h"
#include "Student.h"
#include "DatabaseConnection.h"

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
            admin.displayDashboard();
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