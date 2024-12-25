#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

// Abstract base class for different types of users in the system
class User
{
protected:
    string name;
    string netID;
    string password;

public:
    User(const string& name, const string& netID, const string& password);

    // Pure virtual function to get the user's role
    virtual string getRole() const = 0;

    // Pure virtual function to display user-specific menu 
    virtual void displayMenu() = 0;

    string getNetID() const;
    string getPassword() const;

    // Virtual destructor to support polymorphic deletion
    virtual ~User() = default;
};

#endif