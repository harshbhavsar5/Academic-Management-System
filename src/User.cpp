#include "../include/User.h"
#include <iostream>
using namespace std;

// Default constructor
User::User(){
    userId = 0;
    name = "";
    email = "";
    password = "";
}

// Parameterized constructor
User::User(int userId, string name, string email, string password){
    this->userId = userId;
    this->name = name;
    this->email = email;
    this->password = password;
}

// Setters
void User::setUserId(int userId){
    this->userId = userId;
}

void User::setName(string name){
    this->name = name;
}

void User::setEmail(string email){
    this->email = email;
}

void User::setPassword(string password){
    this->password = password;
}

// Getters
int User::getUserId(){
    return userId;
}

string User::getName(){
    return name;
}

string User::getEmail(){
    return email;
}

string User::getPassword(){
    return password;
}

void User::displayDashboard(){
    cout << "USER DASHBOARD"<<endl;
}

// Destructor
User::~User()
{
}