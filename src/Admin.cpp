#include "../include/Admin.h"
#include <iostream>

using namespace std;

// Default constructor
Admin::Admin() : User()
{
}

// Parameterized constructor
Admin::Admin(
    int userId,
    string name,
    string email,
    string password
) : User(userId, name, email, password)
{
}

void Admin::displayDashboard()
{
    cout << "\n===== ADMIN DASHBOARD =====" << endl;

    cout << "Name: " << getName() << endl;
    cout << "Email: " << getEmail() << endl;

    cout << "\nAvailable Options:" << endl;
    cout << "1. Manage Students" << endl;
    cout << "2. Manage Faculty" << endl;
    cout << "3. Manage Subjects" << endl;
    cout << "4. Manage Course Offerings" << endl;
    cout << "5. Generate Reports" << endl;
    cout << "6. Logout" << endl;
}

Admin::~Admin()
{
}