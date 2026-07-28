#include <iostream>
#include "DatabaseConnection.h"

using namespace std;

int main()
{
    DatabaseConnection database;

    if (!database.connect())
    {
        cout << "Database connection failed." << endl;
        return 1;
    }

    try
    {
        mysqlx::Session* session = database.getSession();

        mysqlx::SqlResult result = session->sql(
            "SELECT student_id, roll_number, full_name, email, "
            "current_semester, admission_year "
            "FROM students"
        ).execute();

        cout << "\n===== STUDENT RECORDS =====" << endl;

        mysqlx::Row row;

        while ((row = result.fetchOne()))
        {
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
    }
    catch (const mysqlx::Error& error)
    {
        cout << "Unable to read student records." << endl;
        cout << "Error: " << error.what() << endl;

        return 1;
    }

    return 0;
}