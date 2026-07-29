#include "../include/StudentManager.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

StudentManager::StudentManager(mysqlx::Session* databaseSession){
    session = databaseSession;
}

void StudentManager::showStudentManagementMenu(){
    int choice = 0;

    while (choice != 6){
        cout << "\n===== STUDENT MANAGEMENT =====" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. View All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student" << endl;
        cout << "5. Deactivate Student" << endl;
        cout << "6. Back to Admin Menu" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1){
            addStudent();
        }
        else if (choice == 2){
            viewAllStudents();
        }
        else if (choice == 3){
            searchStudent();
        }
        else if (choice == 4){
            updateStudent();
        }
        else if (choice == 5){
            deactivateStudent();
        }
        else if (choice == 6){
            cout << "\nReturning to Admin Menu..." << endl;
        }
        else{
            cout << "\nInvalid choice. Enter a number from 1 to 6." << endl;
        }
    }
}

void StudentManager::viewAllStudents(){
    try
    {
    mysqlx::SqlResult result = session->sql(
        "SELECT student_id, "
        "roll_number, "
        "full_name, "
        "email, "
        "current_semester, "
        "admission_year "
        "FROM students "
        "WHERE is_active = 1 "
        "ORDER BY student_id"
    ).execute();

        cout << "\n===== STUDENT RECORDS =====" << endl;

        mysqlx::Row row;
        bool found = false;

        while ((row = result.fetchOne())){
            found = true;

            cout << "\nStudent ID: "
                 << row[0].get<int>() << endl;

            cout << "Roll Number: "
                 << row[1].get<string>() << endl;

            cout << "Name: "
                 << row[2].get<string>() << endl;

            cout << "Email: "
                 << row[3].get<string>() << endl;

            cout << "Current Semester: "
                 << row[4].get<int>() << endl;

            cout << "Admission Year: "
                 << row[5].get<int>() << endl;

            cout << "----------------------------" << endl;
        }

        if (!found){
            cout << "No student records found." << endl;
        }
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to read student records." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void StudentManager::searchStudent(){
    string rollNumber;
    cout << "\nEnter student roll number: ";
    cin >> rollNumber;

    try
    {
        mysqlx::SqlResult result = session->sql(
            "SELECT student_id, roll_number, full_name, email, "
            "department_id, current_semester, admission_year "
            "FROM students "
            "WHERE roll_number = ?"
        )
        .bind(rollNumber)
        .execute();

        mysqlx::Row row = result.fetchOne();

        if (!row){
            cout << "\nNo student found with roll number: "<< rollNumber << endl;
            return;
        }

        cout << "\n===== STUDENT DETAILS =====" << endl;

        cout << "Student ID: "
             << row[0].get<int>() << endl;

        cout << "Roll Number: "
             << row[1].get<string>() << endl;

        cout << "Name: "
             << row[2].get<string>() << endl;

        cout << "Email: "
             << row[3].get<string>() << endl;

        cout << "Department ID: "
             << row[4].get<int>() << endl;

        cout << "Current Semester: "
             << row[5].get<int>() << endl;

        cout << "Admission Year: "
             << row[6].get<int>() << endl;

        cout << "----------------------------" << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to search student." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void StudentManager::addStudent()
{
    string rollNumber;
    string fullName;
    string email;

    int admissionYear;
    int currentSemester;
    int departmentId;

    cout << "\n===== ADD STUDENT =====" << endl;

    cout << "Enter roll number: ";
    cin >> rollNumber;

    cin.ignore();

    cout << "Enter full name: ";
    getline(cin, fullName);

    cout << "Enter email: ";
    getline(cin, email);

    cout << "Enter admission year: ";
    cin >> admissionYear;

    cout << "Enter current semester: ";
    cin >> currentSemester;

    cout << "Enter department ID: ";
    cin >> departmentId;

    if (rollNumber.empty())
    {
        cout << "\nRoll number cannot be empty." << endl;
        return;
    }

    if (fullName.empty())
    {
        cout << "\nStudent name cannot be empty." << endl;
        return;
    }

    if (email.empty())
    {
        cout << "\nEmail cannot be empty." << endl;
        return;
    }

    if (currentSemester < 1 || currentSemester > 8)
    {
        cout << "\nCurrent semester must be between 1 and 8." << endl;
        return;
    }

    try
    {
        mysqlx::SqlResult result = session->sql(
            "INSERT INTO students "
            "(roll_number, full_name, email, admission_year, "
            "current_semester, department_id) "
            "VALUES (?, ?, ?, ?, ?, ?)"
        )
        .bind(
            rollNumber,
            fullName,
            email,
            admissionYear,
            currentSemester,
            departmentId
        )
        .execute();

        cout << "\nStudent added successfully." << endl;
        cout << "Generated Student ID: "
             << result.getAutoIncrementValue() << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to add student." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void StudentManager::updateStudent(){
    string rollNumber;
    cout << "\n===== UPDATE STUDENT =====" << endl;
    cout << "Enter student roll number: ";
    cin >> rollNumber;

    try
    {
        mysqlx::SqlResult result = session->sql(
            "SELECT student_id, full_name "
            "FROM students "
            "WHERE roll_number = ?"
        )
        .bind(rollNumber)
        .execute();

        mysqlx::Row row = result.fetchOne();

        if (!row)
        {
            cout << "\nNo student found with roll number: "
                 << rollNumber << endl;

            return;
        }

        cout << "\nStudent found: "
             << row[1].get<string>() << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to find student." << endl;
        cout << "Error: " << error.what() << endl;
        return;
    }
    int choice;

    while (true)
    {
        cout << "\n===== UPDATE STUDENT MENU =====" << endl;
        cout << "Roll Number: " << rollNumber << endl;

        cout << "\n1. Update Full Name" << endl;
        cout << "2. Update Email" << endl;
        cout << "3. Update Department" << endl;
        cout << "4. Update Current Semester" << endl;
        cout << "5. Update Admission Year" << endl;
        cout << "6. Back to Student Management Menu" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            cout << "\nInvalid input. Enter a number from 1 to 6."<< endl;
            continue;
        }

        if (choice == 1){
            updateStudentName(rollNumber);
        }
        else if (choice == 2){
            updateStudentEmail(rollNumber);
        }
        else if (choice == 3){
            updateStudentDepartment(rollNumber);
        }
        else if (choice == 4){
            updateStudentSemester(rollNumber);
        }
        else if (choice == 5){
            updateStudentAdmissionYear(rollNumber);
        }
        else if (choice == 6){
            cout << "\nReturning to Student Management Menu..."<< endl;

            return;
        }
        else{
            cout << "\nInvalid choice. Enter a number from 1 to 6."<< endl;
        }
    }
}

void StudentManager::updateStudentName(const string& rollNumber){
    string newName;

    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    cout << "\nEnter new full name: ";
    getline(cin, newName);

    if (newName.empty()){
        cout << "\nStudent name cannot be empty." << endl;
        return;
    }

    try
    {
        session->sql(
            "UPDATE students "
            "SET full_name = ? "
            "WHERE roll_number = ?"
        )
        .bind(newName, rollNumber)
        .execute();

        cout << "\nStudent name updated successfully." << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to update student name." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void StudentManager::updateStudentEmail(const string& rollNumber){
    string newEmail;

    cout << "\nEnter new email: ";
    cin >> newEmail;

    if (newEmail.empty()){
        cout << "\nEmail cannot be empty." << endl;
        return;
    }

    if (newEmail.find('@') == string::npos){
        cout << "\nInvalid email. Email must contain @." << endl;
        return;
    }

    try
    {
        session->sql(
            "UPDATE students "
            "SET email = ? "
            "WHERE roll_number = ?"
        )
        .bind(newEmail, rollNumber)
        .execute();

        cout << "\nStudent email updated successfully." << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to update student email." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void StudentManager::updateStudentDepartment(const string& rollNumber){
    int newDepartmentId;

    cout << "\nEnter new department ID: ";
    cin >> newDepartmentId;

    if (cin.fail()){
        cin.clear();

        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout << "\nDepartment ID must be a number." << endl;
        return;
    }

    if (newDepartmentId <= 0){
        cout << "\nDepartment ID must be greater than 0." << endl;
        return;
    }

    try
    {
        mysqlx::SqlResult departmentResult = session->sql(
            "SELECT department_id "
            "FROM departments "
            "WHERE department_id = ?"
        )
        .bind(newDepartmentId)
        .execute();

        mysqlx::Row departmentRow =
            departmentResult.fetchOne();

        if (!departmentRow){
            cout << "\nNo department found with ID: "
                 << newDepartmentId << endl;

            return;
        }

        session->sql(
            "UPDATE students "
            "SET department_id = ? "
            "WHERE roll_number = ?"
        )
        .bind(newDepartmentId, rollNumber)
        .execute();

        cout << "\nStudent department updated successfully."
             << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to update student department." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void StudentManager::updateStudentSemester(const string& rollNumber){ 
    int newSemester;

    cout << "\nEnter new current semester: ";
    cin >> newSemester;

    if (cin.fail()){
        cin.clear();

        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout << "\nSemester must be a number." << endl;
        return;
    }

    if (newSemester < 1 || newSemester > 8){
        cout << "\nSemester must be between 1 and 8."
             << endl;

        return;
    }

    try
    {
        session->sql(
            "UPDATE students "
            "SET current_semester = ? "
            "WHERE roll_number = ?"
        )
        .bind(newSemester, rollNumber)
        .execute();

        cout << "\nStudent semester updated successfully."
             << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to update student semester." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void StudentManager::updateStudentAdmissionYear(const string& rollNumber){
    int newAdmissionYear;

    cout << "\nEnter new admission year: ";
    cin >> newAdmissionYear;

    if (cin.fail()){
        cin.clear();

        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout << "\nAdmission year must be a number."
             << endl;

        return;
    }

    if (newAdmissionYear < 2000 || newAdmissionYear > 2100){
        cout << "\nEnter a valid admission year between "<< "2000 and 2100." << endl;
        return;
    }

    try
    {
        session->sql(
            "UPDATE students "
            "SET admission_year = ? "
            "WHERE roll_number = ?"
        )
        .bind(newAdmissionYear, rollNumber)
        .execute();

        cout << "\nStudent admission year updated successfully."<< endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to update admission year." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void StudentManager::deactivateStudent(){
    string rollNumber;
    char confirm;

    cout << "\n===== DELETE STUDENT =====" << endl;

    cout << "Enter Student Roll Number: ";
    cin >> rollNumber;

    try
    {
        mysqlx::SqlResult result = session->sql(
            "SELECT full_name "
            "FROM students "
            "WHERE roll_number = ? "
            "AND is_active = 1"
        )
        .bind(rollNumber)
        .execute();

        mysqlx::Row row = result.fetchOne();

        if (!row){
            cout << "\nNo active student found with Roll Number: "
                 << rollNumber << endl;
            return;
        }

        cout << "\nStudent Found: "
             << row[0].get<string>() << endl;

        cout << "Are you sure you want to delete this student? (Y/N): ";
        cin >> confirm;

        if (confirm != 'Y' && confirm != 'y'){
            cout << "\nDeletion Cancelled." << endl;
            return;
        }

        mysqlx::SqlResult deleteResult = session->sql(
            "UPDATE students "
            "SET is_active = 0 "
            "WHERE roll_number = ?"
        )
        .bind(rollNumber)
        .execute();

        if(deleteResult.getAffectedItemsCount() > 0){
            cout << "\nStudent deleted successfully." << endl;
        }
        else{
            cout << "\nUnable to delete student." << endl;
        }
    }
    catch(const mysqlx::Error& error){
        cout << "\nDatabase Error!" << endl;
        cout << error.what() << endl;
    }
}

