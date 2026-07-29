#ifndef FACULTY_MANAGER_H
#define FACULTY_MANAGER_H

#include <mysqlx/xdevapi.h>
#include <string>

class FacultyManager{
private:
    mysqlx::Session* session;

    void updateFacultyName(const std::string& employeeId);
    void updateFacultyEmail(const std::string& employeeId);
    void updateFacultyDepartment(const std::string& employeeId);
    void updateFacultyDesignation(const std::string& employeeId);

public:
    FacultyManager(mysqlx::Session* databaseSession);

    void showFacultyManagementMenu();

    void addFaculty();
    void viewAllFaculty();
    void searchFaculty();
    void updateFaculty();
    void deactivateFaculty();
};

#endif