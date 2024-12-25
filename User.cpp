#include "User.h"

using namespace std;

// Constructor: Initializes a user with provided name, netID, and password
User::User(const string& name, const string& netID, const string& password)
{
    this->name = name;
    this->netID = netID;
    this->password = password;
}


// Returns the netID of the user
string User::getNetID() const
{
    return netID;
}

// Returns the password of the user
string User::getPassword() const
{
    return password;
}
