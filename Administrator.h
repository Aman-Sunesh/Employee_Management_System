#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h" 
#include "Course.h"
#include <iostream>
#include <string>

using namespace std;

// Forward declaration of UserManager to resolve circular dependency
class UserManager;

class Administrator : public User {
private:
    string name;
    string netID;
    string password;
    UserManager* U; // Pointer to UserManager

public:
    // Constructors
    Administrator();
    Administrator(const string& name, const string& netID, const string& password);

    // Set UserManager pointer
    void setUserManager(UserManager* userManager);

    // Override User class methods
    virtual string getRole() const override;
    virtual void displayMenu() override;

    string getName();
    string getNetID();

    // Additional methods
    void addStudent();
    void addProfessor();
    void addAdministrator();

    void deleteStudent();
    void deleteProfessor();
    void deleteAdministrator();


    void modifyStudent();
    void modifyProfessor();

    void findUser();

    void manageCourses();

    void viewAllStudents() const;
    void viewAllProfessors() const;
    void viewAllAdministrators() const;
    void displayDetails();

    // Destructor
    virtual ~Administrator();
};

#endif // ADMINISTRATOR_H