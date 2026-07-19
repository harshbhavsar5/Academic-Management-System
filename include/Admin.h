#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>

using namespace std;

class Admin : public User
{
public:
    Admin();

    Admin(
        int userId,
        string name,
        string email,
        string password
    );

    void displayDashboard() override;

    ~Admin() override;
};

#endif