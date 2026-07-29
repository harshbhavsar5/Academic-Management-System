#ifndef ENROLLMENT_MANAGER_H
#define ENROLLMENT_MANAGER_H

#include <mysqlx/xdevapi.h>

class EnrollmentManager
{
private:
    mysqlx::Session* session;

public:
    EnrollmentManager(mysqlx::Session* databaseSession);

    void showEnrollmentManagementMenu();
    void addEnrollment();
    void viewAllEnrollments();
    void searchEnrollment();
    void updateEnrollment();
    void deleteEnrollment();
};

#endif
