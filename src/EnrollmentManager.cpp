#include "../include/EnrollmentManager.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

EnrollmentManager::EnrollmentManager(mysqlx::Session* databaseSession){
    session = databaseSession;
}

void EnrollmentManager::showEnrollmentManagementMenu(){
    int choice = 0;
    while (choice != 6)
    {
        cout << "\n===== ENROLLMENT MANAGEMENT =====" << endl;
        cout << "1. Add Enrollment" << endl;
        cout << "2. View All Enrollments" << endl;
        cout << "3. Search Enrollment" << endl;
        cout << "4. Update Enrollment" << endl;
        cout << "5. Delete Enrollment" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            cout << "\nInvalid input." << endl;
            continue;
        }

        if (choice == 1) addEnrollment();
        else if (choice == 2) viewAllEnrollments();
        else if (choice == 3) searchEnrollment();
        else if (choice == 4) updateEnrollment();
        else if (choice == 5) deleteEnrollment();
        else if (choice == 6) cout << "\nReturning to Main Menu..." << endl;
        else cout << "\nInvalid choice. Enter 1 to 6." << endl;
    }
}

void EnrollmentManager::addEnrollment(){
    int studentId, offeringId;
    string enrolledOn;

    cout << "\n===== ADD ENROLLMENT =====" << endl;
    cout << "Enter student ID: ";
    cin >> studentId;
    cout << "Enter offering ID: ";
    cin >> offeringId;
    cout << "Enter enrollment date (YYYY-MM-DD): ";
    cin >> enrolledOn;

    try{
        mysqlx::Row studentRow = session->sql(
            "SELECT student_id FROM students WHERE student_id = ? AND is_active = 1"
        ).bind(studentId).execute().fetchOne();

        if (!studentRow)
        {
            cout << "\nNo active student found with ID: " << studentId << endl;
            return;
        }

        mysqlx::Row offeringRow = session->sql(
            "SELECT offering_id FROM semester_offerings WHERE offering_id = ?"
        ).bind(offeringId).execute().fetchOne();

        if (!offeringRow)
        {
            cout << "\nNo offering found with ID: " << offeringId << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "INSERT INTO enrollments (student_id, offering_id, enrolled_on) "
            "VALUES (?, ?, ?)"
        ).bind(studentId, offeringId, enrolledOn).execute();

        cout << "\nEnrollment added successfully." << endl;
        cout << "Generated Enrollment ID: " << result.getAutoIncrementValue() << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to add enrollment. The student may already be enrolled." << endl;
        cout << "Error: " << error.what() << endl;
    }
}

void EnrollmentManager::viewAllEnrollments()
{
    try{
        mysqlx::SqlResult result = session->sql(
            "SELECT e.enrollment_id, s.roll_number, s.full_name, "
            "c.course_code, c.course_name, so.semester_number, "
            "so.academic_year, e.enrolled_on "
            "FROM enrollments e "
            "JOIN students s ON e.student_id = s.student_id "
            "JOIN semester_offerings so ON e.offering_id = so.offering_id "
            "JOIN courses c ON so.course_id = c.course_id "
            "ORDER BY e.enrollment_id"
        ).execute();

        cout << "\n===== ENROLLMENT RECORDS =====" << endl;
        mysqlx::Row row;
        bool found = false;

        while ((row = result.fetchOne()))
        {
            found = true;
            cout << "\nEnrollment ID: " << row[0].get<int>() << endl;
            cout << "Student: " << row[1].get<string>() << " - " << row[2].get<string>() << endl;
            cout << "Course: " << row[3].get<string>() << " - " << row[4].get<string>() << endl;
            cout << "Semester: " << row[5].get<int>() << endl;
            cout << "Academic Year: " << row[6].get<string>() << endl;
            cout << "Enrolled On: " << row[7].get<string>() << endl;
            cout << "----------------------------" << endl;
        }

        if (!found) cout << "No enrollment records found." << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to read enrollments.\nError: " << error.what() << endl;
    }
}

void EnrollmentManager::searchEnrollment(){
    int enrollmentId;
    cout << "\nEnter enrollment ID: ";
    cin >> enrollmentId;

    try{
        mysqlx::Row row = session->sql(
            "SELECT e.enrollment_id, s.roll_number, s.full_name, "
            "c.course_code, c.course_name, so.semester_number, "
            "so.academic_year, e.enrolled_on "
            "FROM enrollments e "
            "JOIN students s ON e.student_id = s.student_id "
            "JOIN semester_offerings so ON e.offering_id = so.offering_id "
            "JOIN courses c ON so.course_id = c.course_id "
            "WHERE e.enrollment_id = ?"
        ).bind(enrollmentId).execute().fetchOne();

        if (!row){
            cout << "\nNo enrollment found with ID: " << enrollmentId << endl;
            return;
        }

        cout << "\n===== ENROLLMENT DETAILS =====" << endl;
        cout << "Enrollment ID: " << row[0].get<int>() << endl;
        cout << "Student: " << row[1].get<string>() << " - " << row[2].get<string>() << endl;
        cout << "Course: " << row[3].get<string>() << " - " << row[4].get<string>() << endl;
        cout << "Semester: " << row[5].get<int>() << endl;
        cout << "Academic Year: " << row[6].get<string>() << endl;
        cout << "Enrolled On: " << row[7].get<string>() << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to search enrollment.\nError: " << error.what() << endl;
    }
}

void EnrollmentManager::updateEnrollment(){
    int enrollmentId, newOfferingId;
    string newDate;

    cout << "\n===== UPDATE ENROLLMENT =====" << endl;
    cout << "Enter enrollment ID: ";
    cin >> enrollmentId;

    try{
        mysqlx::Row row = session->sql(
            "SELECT enrollment_id FROM enrollments WHERE enrollment_id = ?"
        ).bind(enrollmentId).execute().fetchOne();

        if (!row){
            cout << "\nNo enrollment found with ID: " << enrollmentId << endl;
            return;
        }

        cout << "Enter new offering ID: ";
        cin >> newOfferingId;
        cout << "Enter new enrollment date (YYYY-MM-DD): ";
        cin >> newDate;

        mysqlx::Row offeringRow = session->sql(
            "SELECT offering_id FROM semester_offerings WHERE offering_id = ?"
        ).bind(newOfferingId).execute().fetchOne();

        if (!offeringRow)
{
            cout << "\nNo offering found with ID: " << newOfferingId << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "UPDATE enrollments SET offering_id = ?, enrolled_on = ? "
            "WHERE enrollment_id = ?"
        ).bind(newOfferingId, newDate, enrollmentId).execute();

        cout << (result.getAffectedItemsCount() > 0
            ? "\nEnrollment updated successfully."
            : "\nNo change was made.") << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to update enrollment.\nError: " << error.what() << endl;
    }
}

void EnrollmentManager::deleteEnrollment(){
    int enrollmentId;
    char confirm;

    cout << "\n===== DELETE ENROLLMENT =====" << endl;
    cout << "Enter enrollment ID: ";
    cin >> enrollmentId;

    try{
        mysqlx::Row row = session->sql(
            "SELECT enrollment_id FROM enrollments WHERE enrollment_id = ?"
        ).bind(enrollmentId).execute().fetchOne();

        if (!row){
            cout << "\nNo enrollment found with ID: " << enrollmentId << endl;
            return;
        }

        cout << "Delete this enrollment and its marks? (Y/N): ";
        cin >> confirm;
        if (confirm != 'Y' && confirm != 'y'){
            cout << "\nDeletion cancelled." << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "DELETE FROM enrollments WHERE enrollment_id = ?"
        ).bind(enrollmentId).execute();

        cout << (result.getAffectedItemsCount() > 0
            ? "\nEnrollment deleted successfully."
            : "\nUnable to delete enrollment.") << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to delete enrollment.\nError: " << error.what() << endl;
    }
}
