#include "Student.h"
#include "Course.h"
#include "CourseManager.h"
#include "Utility.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;


// Constructor initializing Student object with User's constructor
Student::Student(const string& name, const string& netID, const string& password) : User(name, netID, password)
{
    this->name = name;
    this->netID = netID;
    this->password = password;
}


// Returns student role as a string
string Student::getRole() const
{
    return "Student";
}


// Sets CourseManager instance for the student
void Student::setCourseManager(CourseManager* courseManager)
{
    this->C = courseManager;
}

// Displays the student-specific menu and handles user input for menu options
void Student::displayMenu() {

    do
    {
        cout << endl;
        cout << "------------------------------------------\n";
        cout << "|               Student Menu             |\n";
        cout << "| 1. Enroll in Course                    |\n";
        cout << "| 2. Withdraw from Course                |\n";
        cout << "| 3. Display Enrolled Courses            |\n";
        cout << "| 4. Display Available Courses           |\n";
        cout << "| 5. Access Grade Obtained for a Course  |\n";
        cout << "| 6. View GPA                            |\n";
        cout << "| 7. Display Grades                      |\n";
        cout << "| 8. View Announcements                  |\n";
        cout << "| 9. View Office Hours                   |\n";
        cout << "| 10. Exit                               |\n";
        cout << "------------------------------------------\n";

        int choice;

        do {
            cout << "Enter your choice(1-10): ";

            if (isInvalidInput(choice)) // If the input is invalid, isInvalidInput will handle the error message
            {
                continue; // Skip the rest of the loop and prompt the user again
            }

            if (choice < 1 || choice > 10)  // Check if the choice is outside the valid range
            {
                cout << "Error! Invalid Choice. Please enter a number between 1 and 10." << endl;
            }

        } while (choice < 1 || choice > 10); // Repeat until a valid choice is entered


        switch (choice)
        {
        case 1:
        {
            enrollInCourse();
            break;
        }

        case 2:
        {
            withdrawFromCourse();
            break;
        }

        case 3:
        {
            displayEnrolledCourses();
            break;
        }

        case 4:
        {
            displayAvailableCourses();
            break;
        }

        case 5:
        {
            findGrade();
            break;
        }

        case 6:
        {
            viewGPA();
            break;
        }

        case 7:
        {
            displayGrades();
            break;
        }


        case 8:
        {
            viewCourseAnnouncements();
            break;
        }

        case 9:
        {
            viewCourseOfficeHours();
            break;
        }

        case 10:
        {
            cout << "Exiting Student Menu...\n";
            return;  // Return from the function, which will take you back to the previous loop in main
        }

        default:
        {
            cout << "Invalid Input! Please try again.\n";
        }
        }
    } while (true);

}

// Getters and setters implementation for Student's attributes
string Student::getName() const
{
    return name;
}

string Student::getNetID() const
{
    return netID;
}

string Student::getLevel() const
{
    return level;
}

float Student::getGPA() const
{
    return GPA;
}

string Student::getEmail() const
{
    return email;
}

string Student::getMobile() const
{
    return mobile;
}

void Student::setName(string name)
{
    this->name = name;
}

void Student::setLevel(string level)
{
    this->level = level;
}

void Student::setGPA(float GPA)
{
    this->GPA = GPA;
}

void Student::setEmail(string email)
{
    this->email = email;
}

void Student::setMobile(string mobile)
{
    this->mobile = mobile;
}

void Student::displayDetails()
{
    cout << "Name: " << name << endl;
    cout << "NetID: " << netID << endl;
    cout << "Level: " << level << endl;
    cout << "GPA: " << GPA << endl;
    cout << "Email: " << email << endl;
    cout << "Mobile: " << mobile << endl;
    cout << endl;
}


// Enrolls student in a course if not full and if course is found
void Student::enrollInCourse()
{
    string courseCode;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line

    // Loop until valid course code is entered
    do {
        cout << "Enter the course code of the course you would like to enroll for: ";
    } while (isInvalidInput(courseCode));

    cout << endl;

    auto& courseList = C->getCourses();

    // Find the course in the course list
    auto it = find_if(courseList.begin(), courseList.end(), [&courseCode](const Course* course) {
        return course->getCourseCode() == courseCode;
        });

    if (it != courseList.end())
    {
        Course* course = *it;

        // Check if course is not full
        if (course->getNumOfStudentsEnrolled() <= 20)
        {
            enrolledCourses.push_back(course);
            course->incrementEnrollment();
            course->addStudent(this); // Add this student to the course's enrolledStudents
            cout << "Enrolled in " << course->getName() << " successfully." << endl;
            cout << endl;
        }

        else
        {
            cout << "Error! Class " << courseCode << " is full." << endl;
        }
    }

    else
    {
        cout << "Course not found." << endl;
    }

}

// Withdraws student from a course
void Student::withdrawFromCourse()
{
    char ch;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line

    // Loop until valid course code is entered
    do
    {
        string courseCode;

        do {
            cout << "Enter the ID of the course you would like to withdraw: ";
        } while (isInvalidInput(courseCode));


        // Find the course in the course list
        auto it = find_if(enrolledCourses.begin(), enrolledCourses.end(), [&courseCode](const Course* course) {
            return course->getCourseCode() == courseCode;
            });

        if (it != enrolledCourses.end())
        {
            cout << endl;

            do {
                cout << "Are you sure you want to delete course " << courseCode << " (y/n)?: ";
            } while (isInvalidInput(ch));

            if (tolower(ch) == 'y')
            {
                Course* course = *it;
                course->removeStudent(this);  // Remove this student from the course's enrolledStudents list
                course->decrementEnrollment();  // Manually decrement the enrollment count
                enrolledCourses.erase(it);
                cout << "Withdrawn from course " << courseCode << " successfully." << endl;
            }

            else
            {
                cout << "Withdrawal Cancelled" << endl;
            }
        }

        else
        {
            cout << "Course not found" << endl;
        }

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

// Function to display enrolled courses for the student
void Student::displayEnrolledCourses() const
{
    int i = 1; // Counter for listing courses

    cout << "Enrolled Courses for " << name << " (" << netID << "):" << endl;
    cout << endl;

    for (const auto& course : enrolledCourses)
    {
        cout << i << ". " << course->getCourseCode() << " - " << course->getName() << endl;
        i += 1;
    }

    cout << endl;

    if (enrolledCourses.empty())
    {
        cout << "No enrolled courses." << endl;
    }
}

// Displays available courses for enrollment
void Student::displayAvailableCourses() const
{
    if (C->getCourses().empty())
    {
        cout << "No available courses." << endl;
        return;
    }

    for (const auto& course : C->getCourses())
    {
        cout << endl;
        cout << "Name: " << course->getName() << endl;
        cout << "Course Code : " << course->getCourseCode() << endl;
        cout << "Credits: " << course->getCredits() << endl;
        cout << "Description: " << course->getDescription() << endl;
        cout << "Instructor: " << course->getInstructor() << endl;
        cout << "Start Date: " << course->getStartDate() << endl;
        cout << "End Date: " << course->getEndDate() << endl;
        cout << endl;
    }
}


// Sets grade for a course
void Student::setGrade() {
    string courseCode, courseName;
    int grade;

    do {
        cout << "Enter course name: ";
    } while (isInvalidInput(courseName));

    do {
        cout << "Enter course code: ";
    } while (isInvalidInput(courseCode));

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

    do {
        cout << "Enter grade for " << courseCode << ": ";
    } while (isInvalidInput(courseCode));

    CourseGrade courseGrade = { grade, courseName };
    courseGrades[courseCode] = courseGrade;
}

// Sets grade for a specific course
void Student::setGrade(const string& courseCode, const string& courseName, int grade) {
    CourseGrade courseGrade;
    courseGrade.grade = grade;
    courseGrade.courseName = courseName;

    courseGrades[courseCode] = courseGrade;  // Set or update the grade and course name for the given course code
}

// Retrieves grade for a specified course
int Student::getGrade(const string& courseCode) const {
    auto it = courseGrades.find(courseCode); // Try to find the course code in the map
    if (it != courseGrades.end()) { // If found,
        return it->second.grade; // return the grade associated with the course code
    }
    else {
        cerr << "Grade for course " << courseCode << " not found.\n";
        return -1; // Return -1 or any other indicator that the grade was not found
    }
}


// Find grades attained by students in a specific course
void Student::findGrade() const {
    string courseCode;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line

    do {
        cout << "Enter course code to retrieve grade: ";
    } while (isInvalidInput(courseCode));

    auto it = courseGrades.find(courseCode);
    if (it != courseGrades.end())
    {
        cout << "Course: " << it->second.courseName
            << " (" << courseCode << ")"
            << " - Grade: " << it->second.grade << endl;
    }

    else
    {
        cout << "Grade for course code " << courseCode << " not found." << endl;
    }
}


// Displays student's grades for all courses
void Student::displayGrades() const {
    for (const auto& pair : courseGrades)
    {
        const string& courseCode = pair.first;
        const CourseGrade& grade = pair.second;
        cout << courseCode << ": " << grade.grade << " (" << grade.courseName << ")" << endl;
    }
}


void Student::viewCourseAnnouncements() const {
    if (enrolledCourses.empty()) {
        cout << "You are not enrolled in any courses." << endl;
        return;
    }

    string courseCode;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line

    // Loop until valid course code is entered
    do {
        cout << "Enter the course code: ";
    } while (isInvalidInput(courseCode));

    auto it = find_if(enrolledCourses.begin(), enrolledCourses.end(), [&courseCode](const Course* course) {
        return course->getCourseCode() == courseCode;
        });

    if (it == enrolledCourses.end()) {
        cout << "You are not enrolled in a course with the code " << courseCode << "." << endl;
        return;
    }

    Course* selectedCourse = *it;
    const auto& announcements = selectedCourse->getAnnouncements();
    cout << endl;

    cout << "Announcements for " << selectedCourse->getName() << " (" << courseCode << "):" << endl;
    if (announcements.empty()) {
        cout << "No announcements at this time." << endl;
    }
    else {
        for (const auto& announcement : announcements) {
            cout << "- " << announcement << endl;
            cout << endl;
        }
    }
}


// Views office hours for a specified course
void Student::viewCourseOfficeHours() const {
    if (enrolledCourses.empty()) {
        cout << "You are not enrolled in any courses." << endl;
        return;
    }

    string courseCode;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line

    // Loop until valid course code is entered
    do {
        cout << "Enter the course code: ";
    } while (isInvalidInput(courseCode));

    auto it = find_if(enrolledCourses.begin(), enrolledCourses.end(), [&courseCode](const Course* course) {
        return course->getCourseCode() == courseCode;
        });

    if (it == enrolledCourses.end()) {
        cout << "You are not enrolled in a course with the code " << courseCode << "." << endl;
        return;
    }

    Course* selectedCourse = *it;
    cout << "Office hours for " << selectedCourse->getName() << " (" << courseCode << "): " << selectedCourse->getOfficeHours() << endl;
}

void Student::viewGPA() const
{
    cout << "GPA: " << GPA;
}

// Returns map of course grades
map<string, CourseGrade> Student::getGrades() const {
    return courseGrades;
}

// Overloads << operator to output CourseGrade objects
ostream& operator<<(ostream& os, const CourseGrade& grade) {
    os << grade.grade << " (" << grade.courseName << ")";
    return os;
}