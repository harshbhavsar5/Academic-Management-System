#include "DatabaseConnection.h"
#include <iostream>
using namespace std;

DatabaseConnection::DatabaseConnection(){
    session = nullptr;
}

bool DatabaseConnection::connect(){
    try
    {
        session = make_unique<mysqlx::Session>(
            "localhost",
            33060,  
            "root",
            "Harsh@1234"
        );

        session->sql("USE academic_management").execute();

        cout << "Database connected successfully." << endl;
        return true;
    }
    catch (const mysqlx::Error& error)
    {
        cout << "Database connection failed." << endl;
        cout << "Error: " << error.what() << endl;

        return false;
    }
}

mysqlx::Session* DatabaseConnection::getSession()
{
    return session.get();
}

DatabaseConnection::~DatabaseConnection(){
    if (session != nullptr){
        session->close();
    }
}