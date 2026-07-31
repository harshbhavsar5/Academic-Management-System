#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include <mysqlx/xdevapi.h>

class ReportManager{
private:
    mysqlx::Session* session;

public:
    ReportManager(mysqlx::Session* session);

    void showReportMenu();
    void studentResultReport();
};

#endif