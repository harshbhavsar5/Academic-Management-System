#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User {
protected:
    int userId;
    string name;
    string email;
    string password;

public:
    User();

    User(int userId, string name, string email, string password);

    // Setters
    void setUserId(int userId);
    void setName(string name);
    void setEmail(string email);
    void setPassword(string password);

    // Getters
    int getUserId();
    string getName();
    string getEmail();
    string getPassword();

    virtual void displayDashboard();

    virtual ~User();
};
#endif