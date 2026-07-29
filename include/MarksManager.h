#ifndef MARKS_MANAGER_H
#define MARKS_MANAGER_H

#include <mysqlx/xdevapi.h>

class MarksManager
{
private:
    mysqlx::Session* session;

public:
    MarksManager(mysqlx::Session* databaseSession);

    void showMarksManagementMenu();
    void addMarks();
    void viewAllMarks();
    void searchMarks();
    void updateMarks();
    void deleteMarks();
};

#endif
