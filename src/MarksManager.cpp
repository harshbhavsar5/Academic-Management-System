#include "../include/MarksManager.h"
#include <iostream>
#include <limits>

using namespace std;

MarksManager::MarksManager(mysqlx::Session* databaseSession){
    session = databaseSession;
}

void MarksManager::showMarksManagementMenu(){
    int choice = 0;
    while (choice != 6)
    {
        cout << "\n===== MARKS MANAGEMENT =====" << endl;
        cout << "1. Add Marks" << endl;
        cout << "2. View All Marks" << endl;
        cout << "3. Search Marks" << endl;
        cout << "4. Update Marks" << endl;
        cout << "5. Delete Marks" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            cout << "\nInvalid input." << endl;
            continue;
        }

        if (choice == 1) addMarks();
        else if (choice == 2) viewAllMarks();
        else if (choice == 3) searchMarks();
        else if (choice == 4) updateMarks();
        else if (choice == 5) deleteMarks();
        else if (choice == 6) cout << "\nReturning to Main Menu..." << endl;
        else cout << "\nInvalid choice. Enter 1 to 6." << endl;
    }
}

void MarksManager::addMarks(){
    int enrollmentId;
    double internalMarks, endsemMarks;

    cout << "\n===== ADD MARKS =====" << endl;
    cout << "Enter enrollment ID: ";
    cin >> enrollmentId;
    cout << "Enter internal marks (0-40): ";
    cin >> internalMarks;
    cout << "Enter end-semester marks (0-60): ";
    cin >> endsemMarks;

    if (internalMarks < 0 || internalMarks > 40 || endsemMarks < 0 || endsemMarks > 60){
        cout << "\nInternal marks must be 0-40 and end-semester marks 0-60." << endl;
        return;
    }

    try{
        mysqlx::Row enrollmentRow = session->sql(
            "SELECT enrollment_id FROM enrollments WHERE enrollment_id = ?"
        ).bind(enrollmentId).execute().fetchOne();

        if (!enrollmentRow){
            cout << "\nNo enrollment found with ID: " << enrollmentId << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "INSERT INTO marks (enrollment_id, internal_marks, endsem_marks) "
            "VALUES (?, ?, ?)"
        ).bind(enrollmentId, internalMarks, endsemMarks).execute();

        cout << "\nMarks added successfully." << endl;
        cout << "Generated Marks ID: " << result.getAutoIncrementValue() << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to add marks. Marks may already exist for this enrollment." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void MarksManager::viewAllMarks()
{
    try
    {
        mysqlx::SqlResult result = session->sql(
            "SELECT m.marks_id, e.enrollment_id, s.roll_number, s.full_name, "
            "c.course_code, m.internal_marks, m.endsem_marks, "
            "(m.internal_marks + m.endsem_marks) AS total_marks "
            "FROM marks m "
            "JOIN enrollments e ON m.enrollment_id = e.enrollment_id "
            "JOIN students s ON e.student_id = s.student_id "
            "JOIN semester_offerings so ON e.offering_id = so.offering_id "
            "JOIN courses c ON so.course_id = c.course_id "
            "ORDER BY m.marks_id"
        ).execute();

        cout << "\n===== MARKS RECORDS =====" << endl;
        mysqlx::Row row;
        bool found = false;

        while ((row = result.fetchOne()))
        {
            found = true;
            cout << "\nMarks ID: " << row[0].get<int>() << endl;
            cout << "Enrollment ID: " << row[1].get<int>() << endl;
            cout << "Student: " << row[2].get<string>() << " - " << row[3].get<string>() << endl;
            cout << "Course Code: " << row[4].get<string>() << endl;
            cout << "Internal Marks: " << row[5].get<double>() << endl;
            cout << "End-Semester Marks: " << row[6].get<double>() << endl;
            cout << "Total Marks: " << row[7].get<double>() << endl;
            cout << "----------------------------" << endl;
        }

        if (!found) cout << "No marks records found." << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to read marks.\nError: " << error.what() << endl;
    }
}

void MarksManager::searchMarks()
{
    int enrollmentId;
    cout << "\nEnter enrollment ID: ";
    cin >> enrollmentId;

    try
    {
        mysqlx::Row row = session->sql(
            "SELECT m.marks_id, e.enrollment_id, s.roll_number, s.full_name, "
            "c.course_code, m.internal_marks, m.endsem_marks, "
            "(m.internal_marks + m.endsem_marks) AS total_marks "
            "FROM marks m "
            "JOIN enrollments e ON m.enrollment_id = e.enrollment_id "
            "JOIN students s ON e.student_id = s.student_id "
            "JOIN semester_offerings so ON e.offering_id = so.offering_id "
            "JOIN courses c ON so.course_id = c.course_id "
            "WHERE e.enrollment_id = ?"
        ).bind(enrollmentId).execute().fetchOne();

        if (!row)
        {
            cout << "\nNo marks found for enrollment ID: " << enrollmentId << endl;
            return;
        }

        cout << "\n===== MARKS DETAILS =====" << endl;
        cout << "Marks ID: " << row[0].get<int>() << endl;
        cout << "Enrollment ID: " << row[1].get<int>() << endl;
        cout << "Student: " << row[2].get<string>() << " - " << row[3].get<string>() << endl;
        cout << "Course Code: " << row[4].get<string>() << endl;
        cout << "Internal Marks: " << row[5].get<double>() << endl;
        cout << "End-Semester Marks: " << row[6].get<double>() << endl;
        cout << "Total Marks: " << row[7].get<double>() << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to search marks.\nError: " << error.what() << endl;
    }
}

void MarksManager::updateMarks(){
    int enrollmentId;
    double internalMarks, endsemMarks;

    cout << "\n===== UPDATE MARKS =====" << endl;
    cout << "Enter enrollment ID: ";
    cin >> enrollmentId;

    try{
        mysqlx::Row row = session->sql(
            "SELECT marks_id FROM marks WHERE enrollment_id = ?"
        ).bind(enrollmentId).execute().fetchOne();

        if (!row){
            cout << "\nNo marks found for enrollment ID: " << enrollmentId << endl;
            return;
        }

        cout << "Enter new internal marks (0-40): ";
        cin >> internalMarks;
        cout << "Enter new end-semester marks (0-60): ";
        cin >> endsemMarks;

        if (internalMarks < 0 || internalMarks > 40 || endsemMarks < 0 || endsemMarks > 60){
            cout << "\nInternal marks must be 0-40 and end-semester marks 0-60." << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "UPDATE marks SET internal_marks = ?, endsem_marks = ? "
            "WHERE enrollment_id = ?"
        ).bind(internalMarks, endsemMarks, enrollmentId).execute();

        cout << (result.getAffectedItemsCount() > 0
            ? "\nMarks updated successfully."
            : "\nNo change was made.") << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to update marks.\nError: " << error.what() << endl;
    }
}

void MarksManager::deleteMarks(){
    int enrollmentId;
    char confirm;

    cout << "\n===== DELETE MARKS =====" << endl;
    cout << "Enter enrollment ID: ";
    cin >> enrollmentId;

    try{
        mysqlx::Row row = session->sql(
            "SELECT marks_id FROM marks WHERE enrollment_id = ?"
        ).bind(enrollmentId).execute().fetchOne();

        if (!row){
            cout << "\nNo marks found for enrollment ID: " << enrollmentId << endl;
            return;
        }

        cout << "Delete these marks? (Y/N): ";
        cin >> confirm;
        if (confirm != 'Y' && confirm != 'y'){
            cout << "\nDeletion cancelled." << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "DELETE FROM marks WHERE enrollment_id = ?"
        ).bind(enrollmentId).execute();

        cout << (result.getAffectedItemsCount() > 0
            ? "\nMarks deleted successfully."
            : "\nUnable to delete marks.") << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to delete marks.\nError: " << error.what() << endl;
    }
}
