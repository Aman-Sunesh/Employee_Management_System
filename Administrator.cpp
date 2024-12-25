#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits> 
#include <thread>
#include "Administrator.h"
#include "UserManager.h" 
#include "generateAccount.h"
#include "Utility.h"


using namespace std;

inline void clearScreen()
{
    // ANSI escape code to clear screen
    cout << "\x1B[2J\x1B[H";
}

// Default constructor
Administrator::Administrator() : User("Default", "NYUAD", "OOP123")
{
    U = nullptr; // Initialize UserManager pointer to nullptr
}

// Set UserManager pointer
Administrator::Administrator(const string& name, const string& netID, const string& password) : User(name, netID, password)
{
    this->name = name;
    this->netID = netID;
    this->password = password;
    U = nullptr;
}

// Getter Fucntions
string Administrator::getRole() const
{
    return "Administrator";
}

string Administrator::getName()
{
    return name;
}

string Administrator::getNetID()
{
    return netID;
}


// Initialize UserManager pointer to nullptr
void Administrator::setUserManager(UserManager* userManager)
{
    this->U = userManager;
}

// Display menu
void Administrator::displayMenu()
{
    do
    {
        cout << "----------------------------------\n";
        cout << "|        Administrator Menu       |\n";
        cout << "----------------------------------\n";
        cout << "| 1. Add Student                  |\n";
        cout << "| 2. Add Professor                |\n";
        cout << "| 3. Add Administrator            |\n";
        cout << "| 4. Delete Student               |\n";
        cout << "| 5. Delete Professor             |\n";
        cout << "| 6. Delete Administrator         |\n";
        cout << "| 7. Modify Student               |\n";
        cout << "| 8. Modify Professor             |\n";
        cout << "| 9. Find User                    |\n";
        cout << "| 10. Manage Courses              |\n";
        cout << "| 11. View all Students           |\n";
        cout << "| 12. View all Professors         |\n";
        cout << "| 13. View all Administrators     |\n";
        cout << "| 14. Exit                        |\n";
        cout << "----------------------------------\n";
        cout << endl;

        int choice;

        do {
            cout << "Enter your choice(1-14): ";

            if (isInvalidInput(choice)) // If the input is invalid, isInvalidInput will handle the error message
            {
                continue; // Skip the rest of the loop and prompt the user again
            }

            if (choice < 1 || choice > 14)  // Check if the choice is outside the valid range
            {
                cout << "Error! Invalid Choice. Please enter a number between 1 and 14." << endl;
            }

        } while (choice < 1 || choice > 14); // Repeat until a valid choice is entered

        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line

        switch (choice)
        {
        case 1:
        {
            addStudent();
            break;
        }

        case 2:
        {
            addProfessor();
            break;
        }

        case 3:
        {
            addAdministrator();
            break;
        }


        case 4:
        {
            deleteStudent();
            break;
        }

        case 5:
        {
            deleteProfessor();
            break;
        }

        case 6:
        {
            deleteAdministrator();
            break;
        }


        case 7:
        {
            modifyStudent();
            break;
        }

        case 8:
        {
            modifyProfessor();
            break;
        }

        case 9:
        {
            findUser();
            break;
        }

        case 10:
        {
            manageCourses();
            break;
        }

        case 11:
        {
            viewAllStudents();
            break;
        }

        case 12:
        {
            viewAllProfessors();
            break;
        }

        case 13:
        {
            viewAllAdministrators();
            break;
        }

        case 14:
        {
            cout << "Exiting Administrator Menu...\n";
            return;  // Return from the function, which will take you back to the previous loop in main
        }

        default:
        {
            cout << "Invalid Input! Please try again.\n";
        }

        }

    } while (true);
}


// Add student
void Administrator::addStudent()
{
    string name;


    do {
        cout << "Enter full name of student to be added: ";
    } while (isInvalidInput(name));

    // Generating netID and password for the student
    string ID = generateAccount::generateNetID();
    string passwd = generateAccount::generatePassword();

    // Registering the student using UserManager
    U->registerUser(name, ID, passwd, "Student");

    cout << endl;

    cout << "Please note the generated netID and password for " << name << endl;
    cout << "NetID: " << ID;
    cout << "\nPassword: " << passwd;

    cout << endl;

    cout << "Student added succesfully!" << endl;

    // Prompt the user to press enter to continue
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for Enter key

    clearScreen();

}

// Add professor
void Administrator::addProfessor()
{
    string name;

    do {
        cout << "Enter full name of professor to be added: ";
    } while (isInvalidInput(name));

    // Generating netID and password for the professor
    string ID = generateAccount::generateNetID();
    string passwd = generateAccount::generatePassword();

    // Registering the professor using UserManager
    U->registerUser(name, ID, passwd, "Professor");

    cout << endl;

    cout << "Please note the generated netID and password for " << name << endl;
    cout << "NetID: " << ID;
    cout << "\nPassword: " << passwd;

    cout << endl;

    cout << "Professor added succesfully!" << endl;

    // Prompt the user to press enter to continue
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for Enter key

    clearScreen();
}

// Add administrator
void Administrator::addAdministrator()
{
    string name;

    do {
        cout << "Enter full name of administrator to be added: ";
    } while (isInvalidInput(name));

    // Generating netID and password for the administrator
    string ID = generateAccount::generateNetID();
    string passwd = generateAccount::generatePassword();

    // Registering the administrator using UserManager
    U->registerUser(name, ID, passwd, "Administrator");

    cout << endl;

    cout << "Please note the generated netID and password for " << name << endl;
    cout << "NetID: " << ID;
    cout << "\nPassword: " << passwd;

    cout << endl;

    cout << "Administrator added succesfully!" << endl;

    // Prompt the user to press enter to continue
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for Enter key

    clearScreen();
}


// Delete student 
void Administrator::deleteStudent()
{
    do {
        string ID;
        char ch;

        // Prompt user to enter the netID of the student to delete
        do {
            cout << "Enter the netID of the student you want to delete: ";
        } while (isInvalidInput(ID));

        // Search for the student in the user list
        auto it = find_if(U->getUserList().begin(), U->getUserList().end(), [&ID](User* user) {
            return user->getNetID() == ID && user->getRole() == "Student";
            });

        if (it != U->getUserList().end()) {
            cout << endl;
            // Ask for confirmation before deletion
            do {
                cout << "Are you sure you want to delete student " << ID << " (y/n)?: ";
            } while (isInvalidInput(ch));

            if (tolower(ch) == 'y') {
                delete* it;
                U->getUserList().erase(it);
                cout << "Student " << ID << " deleted successfully!" << endl;
            }

            else
            {
                cout << "Deletion canceled." << endl;
            }

            cout << endl;
            // Ask if the user wants to delete another student
            do {
                cout << "Do you want to delete another student (y/n)?: ";
            } while (isInvalidInput(ch));

            if (tolower(ch) != 'y')
            {
                break;
            }
        }

        else
        {
            cout << endl;
            cout << "Student not found." << endl;
            this_thread::sleep_for(chrono::milliseconds(1250));
            clearScreen();
            break;
        }
    } while (true);
}


void Administrator::deleteProfessor()
{
    do {
        string ID;
        char ch;

        // Prompt user to enter the netID of the professor to delete
        do {
            cout << "Enter the netID of the professor you want to delete: ";
        } while (isInvalidInput(ID));

        // Find the professor in the userList using find_if and lambda
        auto it = find_if(U->getUserList().begin(), U->getUserList().end(), [&ID](User* user) {
            return user->getNetID() == ID && user->getRole() == "Professor";
            });

        if (it != U->getUserList().end()) {
            cout << endl;

            // Ask for confirmation before deletion
            do {
                cout << "Are you sure you want to delete professor " << ID << " (y/n)?: ";
            } while (isInvalidInput(ch));

            if (tolower(ch) == 'y') {
                // Delete the professor object and remove it from the list
                delete* it;
                U->getUserList().erase(it);
                cout << "Professor " << ID << " deleted successfully!" << endl;
            }

            else
            {
                cout << "Deletion canceled." << endl;
            }

            cout << endl;

            // Ask if the user wants to delete another professor
            do {
                cout << "Do you want to delete another professor (y/n)?: ";
            } while (isInvalidInput(ch));

            if (tolower(ch) != 'y')
            {
                break; // Exit the loop if user does not want to delete another professor
            }
        }

        else
        {
            cout << "Professor not found." << endl;
            this_thread::sleep_for(chrono::milliseconds(1250));
            clearScreen();
            break; // Exit the loop if the professor is not found
        }
    } while (true);
}


void Administrator::deleteAdministrator()
{
    do {
        string ID;
        char ch;

        // Prompt user to enter the netID of the administrator to delete
        do {
            cout << "Enter the netID of the administrator you want to delete: ";
        } while (isInvalidInput(ID));

        // Find the administrator in the userList using find_if and lambda
        auto it = find_if(U->getUserList().begin(), U->getUserList().end(), [&ID](User* user) {
            return user->getNetID() == ID && user->getRole() == "Administrator";
            });

        if (it != U->getUserList().end()) {
            cout << endl;

            // Ask for confirmation before deletion
            do {
                cout << "Are you sure you want to delete administrator " << ID << " (y/n)?: ";
            } while (isInvalidInput(ch));

            if (tolower(ch) == 'y') {
                // Delete the administrator object and remove it from the list
                delete* it;
                U->getUserList().erase(it);
                cout << "Administrator " << ID << " deleted successfully!" << endl;
            }

            else
            {
                cout << "Deletion canceled." << endl;
            }

            cout << endl;

            // Ask if the user wants to delete another administrator
            do {
                cout << "Do you want to delete another administrator (y/n)?: ";
            } while (isInvalidInput(ch));

            if (tolower(ch) != 'y')
            {
                break; // Exit the loop if user does not want to delete another administrator
            }

        }

        else
        {
            cout << "Administrator not found." << endl;
            this_thread::sleep_for(chrono::milliseconds(1250));
            clearScreen();
            break; // Exit the loop if the administrator is not found
        }

    } while (true);
}


void Administrator::modifyStudent() {
    string ID;

    // Prompt user to enter the netID of the student to modify
    do {
        cout << "Enter the netID of the student you want to modify: ";
    } while (isInvalidInput(ID));

    // Search for the student in the user list
    auto it = find_if(U->getUserList().begin(), U->getUserList().end(), [&ID](User* user) {
        return user->getNetID() == ID && user->getRole() == "Student";
        });

    if (it != U->getUserList().end()) {
        Student* student = dynamic_cast<Student*>(*it);

        if (student != nullptr) {
            cout << "------------------------------------------------" << endl;
            cout << "1. Modify Level" << endl;
            cout << "2. Modify GPA" << endl;
            cout << "3. Modify Email" << endl;
            cout << "4. Modify Mobile" << endl;
            cout << "------------------------------------------------" << endl;

            int choice;

            do {
                cout << "Enter your choice(1-4): ";

                if (isInvalidInput(choice)) // If the input is invalid, isInvalidInput will handle the error message
                {
                    continue; // Skip the rest of the loop and prompt the user again
                }

                if (choice < 1 || choice > 4)  // Check if the choice is outside the valid range
                {
                    cout << "Error! Invalid Choice. Please enter a number between 1 and 4." << endl;
                }

            } while (choice < 1 || choice > 4); // Repeat until a valid choice is entered

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer again after reading the choice

            switch (choice) {
            case 1: {
                string level;
                do {
                    cout << "Enter new level: ";
                } while (isInvalidInput(level));

                student->setLevel(level);
                break;
            }
            case 2: {
                float GPA;
                do {
                    cout << "Enter new GPA: ";
                } while (isInvalidInput(GPA));

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer again
                student->setGPA(GPA);
                break;
            }
            case 3: {
                string email;
                do {
                    cout << "Enter new email: ";
                } while (isInvalidInput(email));

                student->setEmail(email);
                break;
            }
            case 4: {
                string mobile;
                do {
                    cout << "Enter new mobile: ";
                } while (isInvalidInput(mobile));

                student->setMobile(mobile);
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
            cout << "Student details modified successfully!" << endl;
        }
    }
    else {
        cout << "Student not found." << endl;
    }
}


void Administrator::modifyProfessor() {
    string ID;

    // Prompt user to enter the netID of the professor to modify
    do {
        cout << "Enter the netID of the professor you want to modify: ";
    } while (isInvalidInput(ID));

    // Search for the professor in the user list
    auto it = find_if(U->getUserList().begin(), U->getUserList().end(), [&ID](User* user) {
        return user->getNetID() == ID && user->getRole() == "Professor";
        });

    if (it != U->getUserList().end()) {
        Professor* professor = dynamic_cast<Professor*>(*it);

        if (professor != nullptr) {
            cout << "------------------------------------------------" << endl;
            cout << "1. Modify Department" << endl;
            cout << "2. Modify Office Location" << endl;
            cout << "3. Modify Email" << endl;
            cout << "4. Modify Mobile" << endl;
            cout << "------------------------------------------------" << endl;

            int choice;

            do {
                cout << "Enter your choice(1-4): ";

                if (isInvalidInput(choice)) // If the input is invalid, isInvalidInput will handle the error message
                {
                    continue; // Skip the rest of the loop and prompt the user again
                }

                if (choice < 1 || choice > 4)  // Check if the choice is outside the valid range
                {
                    cout << "Error! Invalid Choice. Please enter a number between 1 and 4." << endl;
                }

            } while (choice < 1 || choice > 4); // Repeat until a valid choice is entered

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer again after reading the choice

            switch (choice) {
            case 1: {
                string department;
                do {
                    cout << "Enter new department: ";
                } while (isInvalidInput(department));

                professor->setDepartment(department);
                break;
            }
            case 2: {
                string officeLocation;
                do {
                    cout << "Enter new office location: ";
                } while (isInvalidInput(officeLocation));

                professor->setOfficeLocation(officeLocation);
                break;
            }
            case 3: {
                string email;
                do {
                    cout << "Enter new email: ";
                } while (isInvalidInput(email));

                professor->setEmail(email);
                break;
            }
            case 4: {
                string mobile;
                do {
                    cout << "Enter new mobile: ";
                } while (isInvalidInput(mobile));

                professor->setMobile(mobile);
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
            cout << "Professor details modified successfully!" << endl;
        }
    }
    else {
        cout << "Professor not found." << endl;
    }
}

void Administrator::findUser()
{
    string ID;

    // Prompt user to enter the netID of the user to find
    do {
        cout << "Enter the netID of the user you want to find: ";
    } while (isInvalidInput(ID));

    // Search for the user in the user list
    auto it = find_if(U->getUserList().begin(), U->getUserList().end(), [&ID](User* user) {
        return user->getNetID() == ID;
        });

    if (it != U->getUserList().end())
    {
        User* foundUser = *it; // Dereference iterator to get the User pointer
        string role = foundUser->getRole();

        if (role == "Student")
        {
            Student* student = dynamic_cast<Student*>(foundUser);

            if (student != nullptr)
            {
                cout << endl;
                cout << "Name: " << student->getName() << endl;
                cout << "Role: Student" << endl;
                cout << "NetID: " << student->getNetID() << endl;
                cout << "Level: " << student->getLevel() << endl;
                cout << "GPA: " << student->getGPA() << endl;
                cout << "Email: " << student->getEmail() << endl;
                cout << "Mobile: " << student->getMobile() << endl;
                cout << endl;
            }
        }

        else if (role == "Professor")
        {
            Professor* professor = dynamic_cast<Professor*>(foundUser);

            if (professor != nullptr)
            {
                cout << endl;
                cout << "Name: " << professor->getName() << endl;
                cout << "Role: Professor" << endl;
                cout << "NetID: " << professor->getNetID() << endl;
                cout << "Department: " << professor->getDept() << endl;
                cout << "Office Location: " << professor->getOfficeLoc() << endl;
                cout << "Email: " << professor->getEmail() << endl;
                cout << "Mobile: " << professor->getMobile() << endl;
                cout << endl;
            }
        }

        else if (role == "Administrator")
        {
            Administrator* admin = dynamic_cast<Administrator*>(foundUser);

            if (admin != nullptr)
            {
                cout << endl;
                cout << "Name: " << admin->getName() << endl;
                cout << "Role: Administrator" << endl;
                cout << "NetID: " << admin->getNetID() << endl;
                cout << endl;
            }
        }

        else
        {
            cout << "Error! Unknown Role" << endl;
        }
    }

    else
    {
        cout << "No user found with NetID: " << ID << "\n";
    }
}


// Correctly obtain the singleton instance of CourseManager using the class name
void Administrator::manageCourses()
{
    // Correctly obtain the singleton instance of CourseManager using the class name
    CourseManager* courseManager = CourseManager::getInstance();

    // Set UserManager for the CourseManager instance
    courseManager->setUserManager(U);

    // Display the course management menu
    courseManager->displayMenu(); // Assuming displayMenu() is a public method of CourseManager
}


void Administrator::viewAllStudents() const
{
    for (const auto& user : U->getUserList()) {
        if (user->getRole() == "Student") {
            Student* student = dynamic_cast<Student*>(user); // If user is a student
            if (student != nullptr)
            {
                student->displayDetails();
            }
            else {
                cout << "Failed to cast User to Student." << endl;
            }
        }
    }
}


void Administrator::viewAllProfessors() const
{
    // Iterate over the userList from UserManager
    for (const auto& user : U->getUserList()) {
        if (user->getRole() == "Professor") {
            // Cast the User pointer to Professor pointer safely
            Professor* professor = dynamic_cast<Professor*>(user); // If user is a professor
            if (professor != nullptr) {
                // Call displayDetails function to print professor details
                professor->displayDetails();
            }
        }
    }
}

void Administrator::viewAllAdministrators() const
{
    // Iterate over the userList from UserManager
    for (const auto& user : U->getUserList()) {
        if (user->getRole() == "Administrator") {
            // Cast the User pointer to Administrator pointer safely
            Administrator* admin = dynamic_cast<Administrator*>(user); // If user is a administrator

            if (admin != nullptr) {
                // Assuming Administrator class has a method to display details
                admin->displayDetails();
            }
        }
    }
}

void Administrator::displayDetails()
{
    cout << "Name: " << name << endl;
    cout << "netID: " << netID << endl;
    cout << endl;
}


// Destructor
Administrator::~Administrator()
{
}