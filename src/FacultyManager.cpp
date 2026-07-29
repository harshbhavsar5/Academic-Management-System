    #include "../include/FacultyManager.h"
    #include <iostream>
    #include <limits>
    #include <string>
    using namespace std;

    FacultyManager::FacultyManager(mysqlx::Session* databaseSession){
        session=databaseSession;
    }

    void FacultyManager::showFacultyManagementMenu(){
        int choice=0;
        while(choice!=6){
            cout<<"\n===== FACULTY MANAGER ====="<<endl;
            cout<<"1. Add Faculty"<<endl;
            cout<<"2. View All Faculty"<<endl;
            cout<<"3. Search Faculty"<<endl;
            cout<<"4. Update Faculty"<<endl;
            cout<<"5. Deactivate Faculty"<<endl;
            cout<<"6. Back to Main Menu"<<endl;
            cin>>choice;
            if (choice == 1){
                addFaculty();
            }
            else if (choice == 2){
                viewAllFaculty();
            }
            else if (choice == 3){
                searchFaculty();
            }
            else if (choice == 4){
                updateFaculty();
            }
            else if (choice == 5){
                deactivateFaculty();
            }
            else if (choice == 6){
                cout << "\nReturning to Admin Menu..." << endl;
            }
            else{
                cout << "\nInvalid choice. Enter a number from 1 to 6." << endl;
            }
        }
    }

    void FacultyManager::updateFaculty(){
        string employeeCode;
        cout<<"\n===== UPDATE FACULTY ====="<<endl;
        cout << "Enter Employee Code : ";
        cin >> employeeCode;

        try{
            mysqlx::SqlResult result = session->sql(
                "SELECT employee_code, full_name "
                "FROM faculties "
                "WHERE employee_code = ? "
                "AND is_active = 1"
            )
            .bind(employeeCode)
            .execute();

            mysqlx::Row row = result.fetchOne();

            if (!row)
            {
                cout << "\nNo faculty found with employee code: "
                    << employeeCode << endl;

                return;
            }

            cout << "\nFaculty found: "
                << row[1].get<string>() << endl;
        }
        catch (const mysqlx::Error& error)
        {
            cout << "\nUnable to find faculty." << endl;
            cout << "Error: " << error.what() << endl;
            return;
        }

        int choice=0;
        while(choice!=5){
            cout << "\n1. Update Full Name" << endl;
            cout << "2. Update Email" << endl;
            cout << "3. Update Department" << endl;
            cout << "4. Update Designation" << endl;
            cout << "5. Back to Faculty Management Menu" << endl;

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
                updateFacultyName(employeeCode);
            }
            else if (choice == 2){
                updateFacultyEmail(employeeCode);
            }
            else if (choice == 3){
                updateFacultyDepartment(employeeCode);
            }
            else if (choice == 4){
                updateFacultyDesignation(employeeCode);
            }
            else if (choice == 5){
                cout << "\nReturning to Faculty Management Menu..."<< endl;
                return;
            }
            else{
                cout << "\nInvalid choice. Enter a number from 1 to 5."<< endl;
            }
        }
    }

    void FacultyManager::updateFacultyName(const string& employeeCode){
        string newName;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout << "\nEnter new full name: ";
        getline(cin, newName);

        if (newName.empty()){
            cout << "\nFaculty name cannot be empty." << endl;
            return;
        }

        try{
            session->sql(
                "UPDATE faculties "
                "SET full_name = ? "
                "WHERE employee_code = ? "
                "AND is_active = 1"
            )
            .bind(newName, employeeCode)
            .execute();

            cout << "\nFaculty name updated successfully." << endl;
        }
        catch (const mysqlx::Error& error){
            cout << "\nUnable to update faculty name." << endl;
            cout << "Error: " << error.what() << endl;
        }
    }

    void FacultyManager::updateFacultyEmail(const string& employeeCode){
        string newEmail;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout << "\nEnter new email : ";
        getline(cin, newEmail);

        if (newEmail.empty()){
            cout << "\nEmail cannot be empty." << endl;
            return;
        }

        if (newEmail.find('@') == string::npos){
            cout << "\nInvalid email. Email must contain @." << endl;
            return;
        }

        try{
            session->sql(
                "UPDATE faculties "
                "SET email = ? "
                "WHERE employee_code = ?"
            )
            .bind(newEmail, employeeCode)
            .execute();

            cout << "\nFaculty email updated successfully." << endl;
        }
        catch (const mysqlx::Error& error){
            cout << "\nUnable to update faculty email." << endl;
            cout << "Error: " << error.what() << endl;
        }
    }

    void FacultyManager::updateFacultyDepartment(const string& employeeCode){
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
                cout << "\nNo department found with ID: "<< newDepartmentId << endl;
                return;
            }

            session->sql(
                "UPDATE faculties "
                "SET department_id = ? "
                "WHERE employee_code = ? "
                "AND is_active = 1"
            )
            .bind(newDepartmentId, employeeCode)
            .execute();

            cout << "\nFaculty department updated successfully."<< endl;
        }
        catch (const mysqlx::Error& error){
            cout << "\nUnable to update faculty department." << endl;
            cout << "Error: " << error.what() << endl;
        }
    }

    void FacultyManager::updateFacultyDesignation(const string& employeeCode){
        string newDesignation;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout << "\nEnter new designation: ";
        getline(cin, newDesignation);

        if (newDesignation.empty()){
            cout << "\nFaculty designation cannot be empty." << endl;
            return;
        }

        try{
            session->sql(
                "UPDATE faculties "
                "SET designation = ? "
                "WHERE employee_code = ? "
                "AND is_active = 1"
            )
            .bind(newDesignation, employeeCode)
            .execute();

            cout << "\nFaculty designation updated successfully." << endl;
        }
        catch (const mysqlx::Error& error){
            cout << "\nUnable to update faculty designation." << endl;
            cout << "Error: " << error.what() << endl;
        }
    }

    void FacultyManager::addFaculty(){
        string employeeCode;
        string name;
        string email;
        int departmentId;
        string designation;

        cout << "\n===== ADD FACULTY =====" << endl;

        cout << "Enter employee code : ";
        cin >> employeeCode;

        cin.ignore();

        cout << "Enter name : ";
        getline(cin, name);

        cout << "Enter email : ";
        getline(cin, email);

        cout << "Enter Designation : ";
        getline(cin, designation);

        cout << "Enter department ID: ";
        cin >> departmentId;

        if (employeeCode.empty())
        {
            cout << "\nEmployee Code cannot be empty." << endl;
            return;
        }

        if (name.empty())
        {
            cout << "\nEmployee name cannot be empty." << endl;
            return;
        }

        if (email.empty())
        {
            cout << "\nEmail cannot be empty." << endl;
            return;
        }

        try
        {
            mysqlx::SqlResult result = session->sql(
                "INSERT INTO faculties "
                "(employee_code, full_name, email, department_id, designation) "
                "VALUES (?, ?, ?, ?, ?)"
            )
            .bind(
                employeeCode,
                name,
                email,
                departmentId,
                designation
            )
            .execute();

            cout << "\nFaculty added successfully." << endl;
            cout << "Generated Faculty ID: "<< result.getAutoIncrementValue() << endl;
        }
        catch (const mysqlx::Error& error)
        {
            cout << "\nUnable to add faculty." << endl;
            cout << "Error: " << error.what() << endl;
        }

    }

    void FacultyManager::viewAllFaculty(){
        try{
            mysqlx::SqlResult result = session->sql(
                "SELECT faculty_id, employee_code, full_name, "
                "email, department_id, designation "
                "FROM faculties "
                "WHERE is_active = 1 "
                "ORDER BY faculty_id"
            ).execute();

            cout << "\n===== FACULTY RECORDS =====" << endl;

            mysqlx::Row row;
            bool found = false;

            while ((row = result.fetchOne())){
                found = true;

                cout << "\nFaculty ID: "
                    << row[0].get<int>() << endl;

                cout << "Employee Code: "
                    << row[1].get<string>() << endl;

                cout << "Name: "
                    << row[2].get<string>() << endl;

                cout << "Email: "
                    << row[3].get<string>() << endl;

                cout << "Department ID : "
                    << row[4].get<int>() << endl;

                cout << "Designation : "
                    << row[5].get<string>() << endl;

                cout << "----------------------------" << endl;
            }

            if (!found){
                cout << "No faculty records found." << endl;
            }
        }
        catch (const mysqlx::Error& error){
            cout << "\nUnable to read faculty records." << endl;
            cout << "Error: " << error.what() << endl;
        }
    }

    void FacultyManager::searchFaculty(){
        string empCode;
        cout<<"\n Enter Employee Code : ";
        cin>>empCode;

        try{
            mysqlx::SqlResult result = session->sql(
                "SELECT faculty_id, employee_code, full_name, "
                "email, department_id, designation "
                "FROM faculties "
                "WHERE employee_code = ? "
                "AND is_active = 1"
            )
            .bind(empCode)
            .execute();

            mysqlx::Row row = result.fetchOne();

            if (!row){
                cout << "\nNo facluty found with employee code: "<< empCode << endl;
                return;
            }

            cout << "\n===== Faculty DETAILS =====" << endl;

            cout << "Faculty ID: "
                << row[0].get<int>() << endl;

            cout << "Employee Code: "
                << row[1].get<string>() << endl;

            cout << "Name: "
                << row[2].get<string>() << endl;

            cout << "Email: "
                << row[3].get<string>() << endl;

            cout << "Department ID: "
                << row[4].get<int>() << endl;

            cout << "Designation : "
                << row[5].get<string>() << endl;

            cout << "----------------------------" << endl;
        }
        catch (const mysqlx::Error& error){
            cout << "\nUnable to search faculty." << endl;
            cout << "Error: " << error.what() << endl;
        }
    }

    void FacultyManager::deactivateFaculty(){
        string employeeCode;
        char confirm;

        cout << "\n===== DEACTIVATE FACULTY =====" << endl;

        cout << "Enter faculty employee code: ";
        cin >> employeeCode;

        try
        {
            mysqlx::SqlResult searchResult = session->sql(
                "SELECT full_name "
                "FROM faculties "
                "WHERE employee_code = ? "
                "AND is_active = 1"
            )
            .bind(employeeCode)
            .execute();

            mysqlx::Row row = searchResult.fetchOne();

            if (!row)
            {
                cout << "\nNo active faculty found with employee code: "
                    << employeeCode << endl;
                return;
            }

            cout << "\nFaculty Found: "
                << row[0].get<string>() << endl;

            cout << "Are you sure you want to deactivate this faculty? "
                << "(Y/N): ";

            cin >> confirm;

            if (confirm != 'Y' && confirm != 'y')
            {
                cout << "\nDeactivation cancelled." << endl;
                return;
            }

            mysqlx::SqlResult updateResult = session->sql(
                "UPDATE faculties "
                "SET is_active = 0 "
                "WHERE employee_code = ? "
                "AND is_active = 1"
            )
            .bind(employeeCode)
            .execute();

            if (updateResult.getAffectedItemsCount() > 0)
            {
                cout << "\nFaculty deactivated successfully." << endl;
            }
            else
            {
                cout << "\nUnable to deactivate faculty." << endl;
            }
        }
        catch (const mysqlx::Error& error)
        {
            cout << "\nDatabase error while deactivating faculty."
                << endl;

            cout << "Error: " << error.what() << endl;
        }
    }

