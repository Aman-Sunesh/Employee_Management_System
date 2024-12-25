#include "UserManager.h"
#include "login.h" 
#include "User.h"
#include "Student.h"
#include "Professor.h"
#include "Administrator.h"
#include "CourseManager.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Registers a new user with the specified details
void UserManager::registerUser(const string& name, const string& netID, const string& password, const string& role)
{
    User* newUser = nullptr; // Pointer for new user

    // Create user object based on role
    if (role == "Student")
    {
        newUser = new Student(name, netID, password);
    }

    else if (role == "Professor")
    {
        newUser = new Professor(name, netID, password);
    }

    else if (role == "Administrator")
    {
        newUser = new Administrator(name, netID, password);
    }


    // Add new user to the list if successful
    if (newUser != nullptr)
    {
        userList.push_back(newUser);
        cout << "User Registered Successfully!!!";
        clearScreen();
    }

    else
    {
        cout << "Invalid role specified!";
    }
}


// Handles user login process
void UserManager::loginUser(UserManager* UM)
{
    User* loggedInUser = login(userList); // Attempt login

    if (loggedInUser != nullptr)
    {
        // Use the getRole function from the derived class
        string role = loggedInUser->getRole();

        // On successful login, display user-specific menu
        if (role == "Student")
        {
            // Handle student-specific functionality
            Student* student = (Student*)(loggedInUser);
            if (student != nullptr)
            {
                CourseManager* C = CourseManager::getInstance(); // Get the singleton instance
                student->setCourseManager(C); // Set the CourseManager instance for the student
                student->displayMenu(); // Display student menu
            }
        }
        else if (role == "Professor")
        {
            // Handle professor-specific functionality
            Professor* professor = (Professor*)(loggedInUser);
            if (professor != nullptr)
            {
                professor->displayMenu();  // Display professor menu
            }
        }
        else if (role == "Administrator")
        {
            // Handle administrator-specific functionality
            Administrator* admin = (Administrator*)(loggedInUser);
            if (admin != nullptr)
            {
                admin->setUserManager(UM);  // Associate UserManager with admin
                admin->displayMenu();  // Display admin menu
            }
        }
    }

    else
    {
        cout << "Login Unsuccessful!!!" << endl;
        this_thread::sleep_for(chrono::milliseconds(1250)); // Wait before clearing screen
        clearScreen();
    }
}

vector<User*>& UserManager::getUserList()
{
    return userList;
}