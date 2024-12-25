#include <iostream>
#include <limits>
#include <algorithm>
#include <thread>

#include "CourseManager.h"
#include "UserManager.h"
#include "User.h"
#include "Utility.h"

using namespace std;

inline void clearScreen() {
    // ANSI escape code to clear screen
    cout << "\x1B[2J\x1B[H";
}

// Static member variable initialization
CourseManager* CourseManager::instance = nullptr;

// Function to get the singleton instance of CourseManager
CourseManager* CourseManager::getInstance()
{
    if (!instance) {
        instance = new CourseManager();
    }
    return instance;
}

// Function to set the user manager for the CourseManager
void CourseManager::setUserManager(UserManager* userManager)
{
    this->U = userManager;
}

// Function to set the user manager for the CourseManager
void CourseManager::displayMenu()
{
    int choice;

    do
    {
        cout << endl;
        cout << "----------------------------------\n";
        cout << "|   Course Management Menu       |\n";
        cout << "----------------------------------\n";
        cout << "| 1. Add Course                  |\n";
        cout << "| 2. Delete Course               |\n";
        cout << "| 3. Modify Course               |\n";
        cout << "| 4. Assign Professor to Course  |\n";
        cout << "| 5. View All Courses            |\n";
        cout << "| 6. Exit                        |\n";
        cout << "----------------------------------\n";


        do {
            cout << "Enter your choice(1-6): ";

            if (isInvalidInput(choice)) // If the input is invalid, isInvalidInput will handle the error message
            {
                continue; // Skip the rest of the loop and prompt the user again
            }

            if (choice < 1 || choice > 6)  // Check if the choice is outside the valid range
            {
                cout << "Error! Invalid Choice. Please enter a number between 1 and 6." << endl;
            }

        } while (choice < 1 || choice > 6); // Repeat until a valid choice is entered

        cout << endl;
        cin.clear();

        switch (choice) {
        case 1:
            addCourse();
            break;
        case 2:
            deleteCourse();
            break;
        case 3:
            modifyCourse();
            break;
        case 4:
            assignProfessorToCourse();
            break;
        case 5:
            viewAllCourses();
            break;
        case 6:
            cout << "Exiting Course Management Menu...\n";
            return; // Exit the loop
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (true);
}


// Function to add a new course
void CourseManager::addCourse()
{
    string name, courseCode, description, start_date, end_date;
    int credits;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Input validation loops for course details
    do {
        cout << "Enter course name: ";
    } while (isInvalidInput(name));

    do {
        cout << "Enter course code: ";
    } while (isInvalidInput(courseCode));

    do {
        cout << "Enter course description: ";
    } while (isInvalidInput(description));

    do {
        cout << "Enter start date (YYYY-MM-DD): ";
    } while (isInvalidInput(start_date));


    do {
        cout << "Enter end date (YYYY-MM-DD): ";
    } while (isInvalidInput(end_date));

    do {
        cout << "Enter credits: ";
    } while (isInvalidInput(credits));


    // Create a new course object
    Course* newCourse = new Course(name, courseCode, credits, description, start_date, end_date);

    cout << endl;

    // Prompt to assign a professor
    assignProfessorToCourse(newCourse);

    // Add the course to the list
    courseList.push_back(newCourse);

    cout << endl;

    cout << "Course added successfully.\n";

    this_thread::sleep_for(chrono::milliseconds(1450));
    clearScreen();
}

// Function to delete a course
void CourseManager::deleteCourse()
{
    char ch;

    do {
        string courseCode;

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        do {
            cout << "Enter the course code of the course you want to delete: ";
        } while (isInvalidInput(courseCode));

        auto it = find_if(courseList.begin(), courseList.end(), [&courseCode](const Course* course) {
            return course->getCourseCode() == courseCode;
            });

        if (it != courseList.end())
        {
            cout << endl;

            do {
                cout << "Are you sure you want to delete course " << courseCode << " (y/n)?: ";
            } while (isInvalidInput(ch));

            if (tolower(ch) == 'y')
            {
                delete* it; // Free the allocated memory
                courseList.erase(it); // Remove from the list
                cout << "Course " << courseCode << " deleted successfully!" << endl;
            }
            else
            {
                cout << "Deletion canceled." << endl;
            }
        }

        else
        {
            cout << "Course not found." << endl;
        }

        cout << endl;

        do {
            cout << "Do you want to delete another course (y/n)?: ";
        } while (isInvalidInput(ch));

        // Exit the loop if the user does not want to delete another course
        if (tolower(ch) != 'y')
        {
            break;
        }

    } while (true);
}

void CourseManager::modifyCourse()
{
    string courseCode;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    do {
        cout << "Enter the course code of the course you want to modify: ";
    } while (isInvalidInput(courseCode));


    auto it = find_if(courseList.begin(), courseList.end(), [&courseCode](const Course* course) {
        return course->getCourseCode() == courseCode;
        });

    if (it != courseList.end())
    {
        Course* course = *it; // Dereference iterator to get the Course pointer
        cout << "---------------------------" << endl;
        cout << "1. Modify Credits          " << endl;
        cout << "2. Modify Description      " << endl;
        cout << "3. Modify Instructor       " << endl;
        cout << "4. Modify Start Date       " << endl;
        cout << "5. Modify End Date         " << endl;
        cout << "---------------------------" << endl;
        cout << endl;

        int ch;

        do {
            cout << "Enter your choice(1-7): ";

            if (isInvalidInput(ch)) // If the input is invalid, isInvalidInput will handle the error message
            {
                continue; // Skip the rest of the loop and prompt the user again
            }

            if (ch < 1 || ch > 7)  // Check if the choice is outside the valid range
            {
                cout << "Error! Invalid Choice. Please enter a number between 1 and 7." << endl;
            }

        } while (ch < 1 || ch > 7); // Repeat until a valid choice is entered

        switch (ch)
        {
        case 1:
        {
            int credits;

            do {
                cout << "Enter the new credits: ";
            } while (isInvalidInput(credits));

            course->setCredits(credits);
            break;
        }

        case 2:
        {
            string description;

            do {
                cout << "Enter the new description: ";
            } while (isInvalidInput(description));
            cin.ignore();

            course->setDescription(description);
            break;
        }
        case 3:
        {
            string instructor;
            do {
                cout << "Enter the new instructor name: ";
            } while (isInvalidInput(instructor));

            course->setInstructor(instructor);
            break;
        }

        case 4:
        {
            string startDate;
            do {
                cout << "Enter the new start date: ";
            } while (isInvalidInput(startDate));

            course->setStartDate(startDate);
            break;
        }

        case 5:
        {
            string endDate;
            do {
                cout << "Enter the new end date: ";
            } while (isInvalidInput(endDate));

            course->setEndDate(endDate);
            break;
        }

        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    }

    else
    {
        cout << "Course not found." << endl;
    }
}

// Function to assign a professor to a course
void CourseManager::assignProfessorToCourse(Course* course)
{
    string ID;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    do {
        cout << "Enter the netID of the professor: ";
    } while (isInvalidInput(ID));


    // Find the professor in the user list
    auto it = find_if(U->getUserList().begin(), U->getUserList().end(), [&ID](User* user) {
        return user->getNetID() == ID && user->getRole() == "Professor";
        });

    if (it != U->getUserList().end())
    {
        // Cast the User pointer to Professor pointer
        Professor* professor = dynamic_cast<Professor*>(*it);

        if (professor != nullptr)
        {
            // Add the course to the professor's coursesTaught vector
            professor->addCourseTaught(course);
            // Set the course's instructor to the professor's name
            course->setInstructor(professor->getName());
            cout << endl;
            cout << "Professor assigned to course successfully!" << endl;
            cout << endl;
        }

    }
    else
    {
        cout << "Professor not found." << endl;
        cout << "Please assign professor to the course seperately in the menu" << endl;
    }
}


// Overloaded function to assign a professor to a course without specifying the course
void CourseManager::assignProfessorToCourse()
{
    string courseCode, professorID;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    do {
        cout << "Enter the course code: ";
    } while (isInvalidInput(courseCode));

    // Find the course in the course list
    auto it = find_if(courseList.begin(), courseList.end(), [&courseCode](const Course* course) {
        return course->getCourseCode() == courseCode;
        });

    if (it != courseList.end()) {

        do {
            cout << "Enter the netID of the professor: ";
        } while (isInvalidInput(professorID));

        // Find the professor in the user list
        auto userIt = find_if(U->getUserList().begin(), U->getUserList().end(), [&professorID](User* user) {
            return user->getNetID() == professorID && user->getRole() == "Professor";
            });

        if (userIt != U->getUserList().end())
        {
            // Cast the User pointer to Professor pointer
            Professor* professor = dynamic_cast<Professor*>(*userIt);

            if (professor != nullptr)
            {
                // Add the course to the professor's coursesTaught vector
                professor->addCourseTaught(*it);
                // Set the course's instructor to the professor's name
                (*it)->setInstructor(professor->getName());
                cout << endl;
                cout << "Professor assigned to course successfully!" << endl;
                cout << endl;
            }

            else
            {
                cout << "Failed to cast user to professor." << endl;
            }
        }

        else
        {
            cout << "Professor not found." << endl;
        }
    }

    else
    {
        cout << "Course not found." << endl;
    }
}


// Function to view all courses
void CourseManager::viewAllCourses() const
{
    cout << "Total Courses: " << courseList.size() << "\n"; // Debug output to show total number of courses

    if (courseList.empty())
    {
        cout << "There are no courses available.\n";
        return;
    }
    cout << endl;
    cout << "Available Courses:\n";
    for (const auto& course : courseList)
    {
        cout << endl;
        cout << "Name: " << course->getName() << "\n";
        cout << "Code: " << course->getCourseCode() << "\n";
        cout << "Credits: " << course->getCredits() << "\n";
        cout << "Description: " << course->getDescription() << "\n";
        cout << "Instructor: " << course->getInstructor() << "\n";
        cout << "Start Date: " << course->getStartDate() << "\n";
        cout << "End Date: " << course->getEndDate() << "\n";
        cout << endl;
    }

    cout.flush(); // Ensure all output is flushed to the console

}

// Function to get the list of courses
const vector<Course*>& CourseManager::getCourses() const
{
    return courseList;
}

// Destructor
CourseManager::~CourseManager() {
    for (auto& course : courseList) {
        delete course;
    }
}