#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H
#include <mysqlx/xdevapi.h>
#include <memory>
using namespace std;

class DatabaseConnection
{
private:
    //unique ptr deletes the ptr after use automatically
    unique_ptr<mysqlx::Session> session;

public:
    DatabaseConnection();

    bool connect();

    //getter
    mysqlx::Session* getSession();

    ~DatabaseConnection();
};

#endif