#include "../include/ReportManager.h"

#include <iostream>
#include <string>

using namespace std;

// Parameterized constructor
ReportManager::ReportManager(mysqlx::Session* session)
{
    this->session = session;
}

void ReportManager::showReportMenu()
{
    int choice = 0;

    while (choice != 2)
    {
        cout << "\n========== REPORTS ==========" << endl;
        cout << "1. Student Result Report" << endl;
        cout << "2. Back to Admin Menu" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            studentResultReport();
        }
        else if (choice == 2)
        {
            cout << "\nReturning to admin menu..." << endl;
        }
        else
        {
            cout << "\nInvalid choice. Enter a number from 1 to 2." << endl;
        }
    }
}

void ReportManager::studentResultReport()
{
    string rollNumber;

    cout << "\n===== STUDENT RESULT REPORT =====" << endl;
    cout << "Enter Student Roll Number: ";
    cin >> rollNumber;

    try
    {
        mysqlx::RowResult result = session->sql(
            "SELECT s.roll_number, s.full_name, "
            "c.course_code, c.course_name, "
            "so.semester_number, so.academic_year, "
            "m.internal_marks, m.endsem_marks, "
            "(m.internal_marks + m.endsem_marks) AS total_marks, "
            "CASE "
            "WHEN (m.internal_marks + m.endsem_marks) >= 90 THEN 'A+' "
            "WHEN (m.internal_marks + m.endsem_marks) >= 80 THEN 'A' "
            "WHEN (m.internal_marks + m.endsem_marks) >= 70 THEN 'B' "
            "WHEN (m.internal_marks + m.endsem_marks) >= 60 THEN 'C' "
            "WHEN (m.internal_marks + m.endsem_marks) >= 50 THEN 'D' "
            "ELSE 'F' "
            "END AS grade "
            "FROM students s "
            "JOIN enrollments e ON s.student_id = e.student_id "
            "JOIN semester_offerings so ON e.offering_id = so.offering_id "
            "JOIN courses c ON so.course_id = c.course_id "
            "JOIN marks m ON e.enrollment_id = m.enrollment_id "
            "WHERE s.roll_number = ? "
            "ORDER BY so.academic_year, so.semester_number, c.course_code"
        ).bind(rollNumber).execute();

        mysqlx::Row row = result.fetchOne();

        if (!row)
        {
            cout << "\nNo result records found for Roll Number: "
                 << rollNumber << endl;
            return;
        }

        cout << "\n========== STUDENT RESULT ==========" << endl;
        cout << "Roll Number: " << row[0].get<string>() << endl;
        cout << "Student Name: " << row[1].get<string>() << endl;

        do
        {
            cout << "\n----------------------------------------" << endl;

            cout << "Course Code: "
                 << row[2].get<string>() << endl;

            cout << "Course Name: "
                 << row[3].get<string>() << endl;

            cout << "Semester: "
                 << row[4].get<int>() << endl;

            cout << "Academic Year: "
                 << row[5].get<string>() << endl;

            cout << "Internal Marks: "
                 << row[6].get<double>() << " / 40" << endl;

            cout << "End Semester Marks: "
                 << row[7].get<double>() << " / 60" << endl;

            cout << "Total Marks: "
                 << row[8].get<double>() << " / 100" << endl;

            cout << "Grade: "
                 << row[9].get<string>() << endl;

            row = result.fetchOne();

        } while (row);

        cout << "----------------------------------------" << endl;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "\nUnable to generate student result report." << endl;
        cout << "Error: " << error.what() << endl;
    }
}