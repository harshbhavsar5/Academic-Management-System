#ifndef SEMESTER_OFFERING_MANAGER_H
#define SEMESTER_OFFERING_MANAGER_H

#include <mysqlx/xdevapi.h>

class SemesterOfferingManager
{
private:
    mysqlx::Session* session;

public:
    SemesterOfferingManager(mysqlx::Session* databaseSession);

    void showSemesterOfferingMenu();
    void addOffering();
    void viewAllOfferings();
    void searchOffering();
    void updateOffering();
    void deleteOffering();
};

#endif
