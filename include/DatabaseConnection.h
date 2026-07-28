#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <mysqlx/xdevapi.h>
#include <memory>

class DatabaseConnection
{
private:
    std::unique_ptr<mysqlx::Session> session;

public:
    DatabaseConnection();

    bool connect();

    mysqlx::Session* getSession();

    ~DatabaseConnection();
};

#endif