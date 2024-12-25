#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include <string>
#include "User.h"
#include "Student.h"
#include "Professor.h"
#include "Administrator.h"
#include "CourseManager.h"

using namespace std;

class UserManager {
private:
    vector<User*> userList;

public:
    void registerUser(const string& name, const string& netID, const string& password, const string& role);
    void loginUser(UserManager* UM);
    vector<User*>& getUserList();
};

#endif // USERMANAGER_H