#include "../include/CourseManager.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

CourseManager::CourseManager(mysqlx::Session* databaseSession){
    session = databaseSession;
}

void CourseManager::showCourseManagementMenu(){
    int choice = 0;

    while (choice != 6){
        cout << "\n===== COURSE MANAGEMENT =====" << endl;
        cout << "1. Add Course" << endl;
        cout << "2. View All Courses" << endl;
        cout << "3. Search Course" << endl;
        cout << "4. Update Course" << endl;
        cout << "5. Delete Course" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Enter a number from 1 to 6." << endl;
            choice = 0;
            continue;
        }

        if (choice == 1) addCourse();
        else if (choice == 2) viewAllCourses();
        else if (choice == 3) searchCourse();
        else if (choice == 4) updateCourse();
        else if (choice == 5) deleteCourse();
        else if (choice == 6) cout << "\nReturning to Main Menu..." << endl;
        else cout << "\nInvalid choice. Enter a number from 1 to 6." << endl;
    }
}

void CourseManager::addCourse(){
    string courseCode, courseName;
    int credits, departmentId;

    cout << "\n===== ADD COURSE =====" << endl;
    cout << "Enter course code: ";
    cin >> courseCode;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter course name: ";
    getline(cin, courseName);

    cout << "Enter credits (1-5): ";
    cin >> credits;
    cout << "Enter department ID: ";
    cin >> departmentId;

    if (courseCode.empty() || courseName.empty()){
        cout << "\nCourse code and name cannot be empty." << endl;
        return;
    }

    if (credits < 1 || credits > 5){
        cout << "\nCredits must be between 1 and 5." << endl;
        return;
    }

    try{
        mysqlx::Row departmentRow = session->sql(
            "SELECT department_id FROM departments WHERE department_id = ?"
        ).bind(departmentId).execute().fetchOne();

        if (!departmentRow){
            cout << "\nNo department found with ID: " << departmentId << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "INSERT INTO courses "
            "(course_code, course_name, credits, department_id) "
            "VALUES (?, ?, ?, ?)"
        ).bind(courseCode, courseName, credits, departmentId).execute();

        cout << "\nCourse added successfully." << endl;
        cout << "Generated Course ID: " << result.getAutoIncrementValue() << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to add course." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void CourseManager::viewAllCourses(){
    try
    {
        mysqlx::SqlResult result = session->sql(
            "SELECT c.course_id, c.course_code, c.course_name, c.credits, "
            "d.department_name "
            "FROM courses c "
            "JOIN departments d ON c.department_id = d.department_id "
            "ORDER BY c.course_id"
        ).execute();

        cout << "\n===== COURSE RECORDS =====" << endl;
        mysqlx::Row row;
        bool found = false;

        while ((row = result.fetchOne()))
        {
            found = true;
            cout << "\nCourse ID: " << row[0].get<int>() << endl;
            cout << "Course Code: " << row[1].get<string>() << endl;
            cout << "Course Name: " << row[2].get<string>() << endl;
            cout << "Credits: " << row[3].get<int>() << endl;
            cout << "Department: " << row[4].get<string>() << endl;
            cout << "----------------------------" << endl;
        }

        if (!found) cout << "No course records found." << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to read course records." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void CourseManager::searchCourse(){
    string courseCode;
    cout << "\nEnter course code: ";
    cin >> courseCode;

    try{
        mysqlx::Row row = session->sql(
            "SELECT c.course_id, c.course_code, c.course_name, c.credits, "
            "d.department_name "
            "FROM courses c "
            "JOIN departments d ON c.department_id = d.department_id "
            "WHERE c.course_code = ?"
        ).bind(courseCode).execute().fetchOne();

        if (!row){
            cout << "\nNo course found with code: " << courseCode << endl;
            return;
        }

        cout << "\n===== COURSE DETAILS =====" << endl;
        cout << "Course ID: " << row[0].get<int>() << endl;
        cout << "Course Code: " << row[1].get<string>() << endl;
        cout << "Course Name: " << row[2].get<string>() << endl;
        cout << "Credits: " << row[3].get<int>() << endl;
        cout << "Department: " << row[4].get<string>() << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to search course." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void CourseManager::updateCourse(){
    string courseCode;
    cout << "\n===== UPDATE COURSE =====" << endl;
    cout << "Enter course code: ";
    cin >> courseCode;

    try
    {
        mysqlx::Row row = session->sql(
            "SELECT course_name FROM courses WHERE course_code = ?"
        ).bind(courseCode).execute().fetchOne();

        if (!row)
        {
            cout << "\nNo course found with code: " << courseCode << endl;
            return;
        }

        cout << "Course Found: " << row[0].get<string>() << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to find course." << endl;
        cout << "Error: " << error.what() << endl;
        return;
    }

    int choice = 0;
    while (choice != 4)
    {
        cout << "\n1. Update Course Name" << endl;
        cout << "2. Update Credits" << endl;
        cout << "3. Update Department" << endl;
        cout << "4. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) updateCourseName(courseCode);
        else if (choice == 2) updateCourseCredits(courseCode);
        else if (choice == 3) updateCourseDepartment(courseCode);
        else if (choice == 4) return;
        else cout << "\nInvalid choice. Enter a number from 1 to 4." << endl;
    }
}

void CourseManager::updateCourseName(const string& courseCode){
    string newName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter new course name: ";
    getline(cin, newName);

    if (newName.empty()){
        cout << "\nCourse name cannot be empty." << endl;
        return;
    }

    try{
        mysqlx::SqlResult result = session->sql(
            "UPDATE courses SET course_name = ? WHERE course_code = ?"
        ).bind(newName, courseCode).execute();

        cout << (result.getAffectedItemsCount() > 0
            ? "\nCourse name updated successfully."
            : "\nNo change was made.") << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to update course name.\nError: " << error.what() << endl;
    }
}

void CourseManager::updateCourseCredits(const string& courseCode){
    int newCredits;
    cout << "Enter new credits (1-5): ";
    cin >> newCredits;

    if (newCredits < 1 || newCredits > 5){
        cout << "\nCredits must be between 1 and 5." << endl;
        return;
    }

    try{
        mysqlx::SqlResult result = session->sql(
            "UPDATE courses SET credits = ? WHERE course_code = ?"
        ).bind(newCredits, courseCode).execute();

        cout << (result.getAffectedItemsCount() > 0
            ? "\nCourse credits updated successfully."
            : "\nNo change was made.") << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to update credits.\nError: " << error.what() << endl;
    }
}

void CourseManager::updateCourseDepartment(const string& courseCode){
    int departmentId;
    cout << "Enter new department ID: ";
    cin >> departmentId;

    try{
        mysqlx::Row departmentRow = session->sql(
            "SELECT department_id FROM departments WHERE department_id = ?"
        ).bind(departmentId).execute().fetchOne();

        if (!departmentRow){
            cout << "\nNo department found with ID: " << departmentId << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "UPDATE courses SET department_id = ? WHERE course_code = ?"
        ).bind(departmentId, courseCode).execute();

        cout << (result.getAffectedItemsCount() > 0
            ? "\nCourse department updated successfully."
            : "\nNo change was made.") << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to update department.\nError: " << error.what() << endl;
    }
}

void CourseManager::deleteCourse()
{
    string courseCode;
    char confirm;

    cout << "\n===== DELETE COURSE =====" << endl;
    cout << "Enter course code: ";
    cin >> courseCode;

    try
    {
        mysqlx::SqlResult searchResult = session->sql(
            "SELECT course_name "
            "FROM courses "
            "WHERE course_code = ?"
        ).bind(courseCode).execute();

        mysqlx::Row row = searchResult.fetchOne();

        if (!row)
        {
            cout << "\nNo course found with code: "
                 << courseCode << endl;

            return;
        }

        cout << "Course Found: "
             << row[0].get<string>() << endl;

        cout << "Delete this course? (Y/N): ";
        cin >> confirm;

        if (confirm != 'Y' && confirm != 'y')
        {
            cout << "\nDeletion cancelled." << endl;
            return;
        }

        mysqlx::SqlResult deleteResult = session->sql(
            "DELETE FROM courses WHERE course_code = ?"
        ).bind(courseCode).execute();

        if (deleteResult.getAffectedItemsCount() > 0)
        {
            cout << "\nCourse deleted successfully." << endl;
        }
        else
        {
            cout << "\nCourse was not deleted." << endl;
        }
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to delete course." << endl;
        cout << "The course may be used in semester offerings." << endl;
        cout << "Error: " << error.what() << endl;

        return;
    }
}
