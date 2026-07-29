#include "../include/SemesterOfferingManager.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

SemesterOfferingManager::SemesterOfferingManager(mysqlx::Session* databaseSession){
    session = databaseSession;
}

void SemesterOfferingManager::showSemesterOfferingMenu(){
    int choice = 0;
    while (choice != 6)
    {
        cout << "\n===== SEMESTER OFFERING MANAGEMENT =====" << endl;
        cout << "1. Add Offering" << endl;
        cout << "2. View All Offerings" << endl;
        cout << "3. Search Offering" << endl;
        cout << "4. Update Offering" << endl;
        cout << "5. Delete Offering" << endl;
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

        if (choice == 1) addOffering();
        else if (choice == 2) viewAllOfferings();
        else if (choice == 3) searchOffering();
        else if (choice == 4) updateOffering();
        else if (choice == 5) deleteOffering();
        else if (choice == 6) cout << "\nReturning to Main Menu..." << endl;
        else cout << "\nInvalid choice. Enter 1 to 6." << endl;
    }
}

void SemesterOfferingManager::addOffering(){
    int courseId, semesterNumber;
    string academicYear;

    cout << "\n===== ADD SEMESTER OFFERING =====" << endl;
    cout << "Enter course ID: ";
    cin >> courseId;
    cout << "Enter semester number (1-8): ";
    cin >> semesterNumber;
    cout << "Enter academic year (example 2026-2027): ";
    cin >> academicYear;

    if (semesterNumber < 1 || semesterNumber > 8){
        cout << "\nSemester number must be between 1 and 8." << endl;
        return;
    }

    try{
        mysqlx::Row courseRow = session->sql(
            "SELECT course_id FROM courses WHERE course_id = ?"
        ).bind(courseId).execute().fetchOne();

        if (!courseRow)
        {
            cout << "\nNo course found with ID: " << courseId << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "INSERT INTO semester_offerings "
            "(course_id, semester_number, academic_year) VALUES (?, ?, ?)"
        ).bind(courseId, semesterNumber, academicYear).execute();

        cout << "\nOffering added successfully." << endl;
        cout << "Generated Offering ID: " << result.getAutoIncrementValue() << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to add offering.\nError: " << error.what() << endl;
    }
}

void SemesterOfferingManager::viewAllOfferings(){
    try{
        mysqlx::SqlResult result = session->sql(
            "SELECT so.offering_id, c.course_code, c.course_name, "
            "so.semester_number, so.academic_year "
            "FROM semester_offerings so "
            "JOIN courses c ON so.course_id = c.course_id "
            "ORDER BY so.offering_id"
        ).execute();

        cout << "\n===== SEMESTER OFFERINGS =====" << endl;
        mysqlx::Row row;
        bool found = false;

        while ((row = result.fetchOne())){
            found = true;
            cout << "\nOffering ID: " << row[0].get<int>() << endl;
            cout << "Course Code: " << row[1].get<string>() << endl;
            cout << "Course Name: " << row[2].get<string>() << endl;
            cout << "Semester: " << row[3].get<int>() << endl;
            cout << "Academic Year: " << row[4].get<string>() << endl;
            cout << "----------------------------" << endl;
        }

        if (!found) cout << "No semester offerings found." << endl;
    }
    catch (const mysqlx::Error& error){
        cout << "\nUnable to read offerings.\nError: " << error.what() << endl;
    }
}

void SemesterOfferingManager::searchOffering(){
    int offeringId;
    cout << "\nEnter offering ID: ";
    cin >> offeringId;

    try{
        mysqlx::Row row = session->sql(
            "SELECT so.offering_id, c.course_code, c.course_name, "
            "so.semester_number, so.academic_year "
            "FROM semester_offerings so "
            "JOIN courses c ON so.course_id = c.course_id "
            "WHERE so.offering_id = ?"
        ).bind(offeringId).execute().fetchOne();

        if (!row)
        {
            cout << "\nNo offering found with ID: " << offeringId << endl;
            return;
        }

        cout << "\n===== OFFERING DETAILS =====" << endl;
        cout << "Offering ID: " << row[0].get<int>() << endl;
        cout << "Course Code: " << row[1].get<string>() << endl;
        cout << "Course Name: " << row[2].get<string>() << endl;
        cout << "Semester: " << row[3].get<int>() << endl;
        cout << "Academic Year: " << row[4].get<string>() << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to search offering.\nError: " << error.what() << endl;
    }
}

void SemesterOfferingManager::updateOffering(){
    int offeringId, courseId, semesterNumber;
    string academicYear;

    cout << "\n===== UPDATE OFFERING =====" << endl;
    cout << "Enter offering ID: ";
    cin >> offeringId;

    try
    {
        mysqlx::Row row = session->sql(
            "SELECT offering_id FROM semester_offerings WHERE offering_id = ?"
        ).bind(offeringId).execute().fetchOne();

        if (!row)
        {
            cout << "\nNo offering found with ID: " << offeringId << endl;
            return;
        }

        cout << "Enter new course ID: ";
        cin >> courseId;
        cout << "Enter new semester number (1-8): ";
        cin >> semesterNumber;
        cout << "Enter new academic year: ";
        cin >> academicYear;

        if (semesterNumber < 1 || semesterNumber > 8)
        {
            cout << "\nSemester number must be between 1 and 8." << endl;
            return;
        }

        mysqlx::Row courseRow = session->sql(
            "SELECT course_id FROM courses WHERE course_id = ?"
        ).bind(courseId).execute().fetchOne();

        if (!courseRow)
        {
            cout << "\nNo course found with ID: " << courseId << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "UPDATE semester_offerings "
            "SET course_id = ?, semester_number = ?, academic_year = ? "
            "WHERE offering_id = ?"
        ).bind(courseId, semesterNumber, academicYear, offeringId).execute();

        cout << (result.getAffectedItemsCount() > 0
            ? "\nOffering updated successfully."
            : "\nNo change was made.") << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to update offering.\nError: " << error.what() << endl;
    }
}

void SemesterOfferingManager::deleteOffering()
{
    int offeringId;
    char confirm;

    cout << "\n===== DELETE OFFERING =====" << endl;
    cout << "Enter offering ID: ";
    cin >> offeringId;

    try
    {
        mysqlx::Row row = session->sql(
            "SELECT offering_id FROM semester_offerings WHERE offering_id = ?"
        ).bind(offeringId).execute().fetchOne();

        if (!row)
        {
            cout << "\nNo offering found with ID: " << offeringId << endl;
            return;
        }

        cout << "Delete this offering? (Y/N): ";
        cin >> confirm;
        if (confirm != 'Y' && confirm != 'y')
        {
            cout << "\nDeletion cancelled." << endl;
            return;
        }

        mysqlx::SqlResult result = session->sql(
            "DELETE FROM semester_offerings WHERE offering_id = ?"
        ).bind(offeringId).execute();

        cout << (result.getAffectedItemsCount() > 0
            ? "\nOffering deleted successfully."
            : "\nUnable to delete offering.") << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to delete offering. It may have enrollments." << endl;
        cout << "Error: " << error.what() << endl;
    }
}
