#include "Professor.h"
#include "Course.h"
#include "User.h"
#include "Student.h"
#include "Utility.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

// ----------------------------------------------------------------------
// Constructor
Professor::Professor(const std::string& name, const std::string& netID, const std::string& password)
    : User(name, netID, password)
{
    this->name = name;
    this->netID = netID;
    this->password = password;
}

// ----------------------------------------------------------------------
// Returns role
std::string Professor::getRole() const {
    return "Professor";
}

// ----------------------------------------------------------------------
// Overload #1: Numeric input with range
template <typename T>
T Professor::getValidatedInput(const std::string& prompt, T minVal, T maxVal) const
{
    T value;
    bool valid = false;
    do {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
        }
        else if (value < minVal || value > maxVal) {
            std::cout << "Value must be between "
                      << minVal << " and " << maxVal << ". Try again.\n";
        }
        else {
            valid = true;
        }
    } while (!valid);

    // Clear leftover newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Explicit instantiation if needed
template int Professor::getValidatedInput<int>(const std::string&, int, int) const;

// ----------------------------------------------------------------------
// Overload #2: Single-argument function for strings
std::string Professor::getValidatedInput(const std::string& prompt) const
{
    std::string value;
    bool valid = false;
    do {
        std::cout << prompt;
        if (!std::getline(std::cin, value)) {
            std::cin.clear();
            std::cout << "Invalid input. Try again.\n";
        }
        else if (value.empty()) {
            std::cout << "Please enter a non-empty string.\n";
        }
        else {
            valid = true;
        }
    } while (!valid);

    return value;
}

// ----------------------------------------------------------------------
// Menu
void Professor::displayMenu() {
    do {
        std::cout << "\n--------------------------------\n";
        std::cout << "|         Professor Menu       |\n";
        std::cout << "| 1. View Courses Taught       |\n";
        std::cout << "| 2. View Students in a Course |\n";
        std::cout << "| 3. Post Announcements        |\n";
        std::cout << "| 4. Post Office Hours         |\n";
        std::cout << "| 5. Assign Grades             |\n";
        std::cout << "| 6. View Grades of Class      |\n";
        std::cout << "| 7. Exit                      |\n";
        std::cout << "--------------------------------\n";

        // For numeric input, use the 3-arg overload
        int choice = getValidatedInput<int>("Enter your choice (1-7): ", 1, 7);

        switch (choice) {
        case 1: viewCourses(); break;
        case 2: viewStudentsInCourse(); break;
        case 3: postAnnouncement(); break;
        case 4: setOfficeHours(); break;
        case 5: assignGrades(); break;
        case 6: viewStudentGrades(); break;
        case 7:
            std::cout << "Exiting Professor Menu...\n";
            return;
        }
    } while (true);
}

// ----------------------------------------------------------------------
// Getters/Setters
std::string Professor::getName() const      { return name; }
std::string Professor::getNetID() const     { return netID; }
std::string Professor::getDept() const      { return department; }
std::string Professor::getOfficeLoc() const { return officeLocation; }
std::string Professor::getEmail() const     { return email; }
std::string Professor::getMobile() const    { return mobile; }

void Professor::setDepartment(std::string department)      { this->department = department; }
void Professor::setOfficeLocation(std::string officeLocation){ this->officeLocation = officeLocation; }
void Professor::setEmail(std::string email)                { this->email = email; }
void Professor::setMobile(std::string mobile)              { this->mobile = mobile; }

// ----------------------------------------------------------------------
// displayDetails
void Professor::displayDetails() {
    std::cout << "\nName: " << name << "\n";
    std::cout << "NetID: " << netID << "\n";
    std::cout << "Department: " << department << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Mobile: " << mobile << "\n\n";
}

// ----------------------------------------------------------------------
// View courses
void Professor::viewCourses() const {
    if (coursesTaught.empty()) {
        std::cout << "You are not currently teaching any courses.\n";
        return;
    }

    std::cout << "Courses taught by " << name << ":\n";
    for (const auto* course : coursesTaught) {
        std::cout << "\nName: " << course->getName()
                  << "\nCourse Code: " << course->getCourseCode() << "\n";
    }
}

// ----------------------------------------------------------------------
// Add a course
void Professor::addCourseTaught(Course* course) {
    coursesTaught.push_back(course);
}

// ----------------------------------------------------------------------
// View students in a course
void Professor::viewStudentsInCourse() const {
    if (coursesTaught.empty()) {
        std::cout << "You are not currently teaching any courses.\n";
        return;
    }

    // Single-arg function for strings
    std::string courseCode = getValidatedInput("Enter the course code: ");
    auto* it = findCourse(courseCode);
    if (!it) {
        std::cout << "You are not teaching a course with the code " << courseCode << "\n";
        return;
    }

    const auto& enrolledStudents = it->getEnrolledStudents();
    if (enrolledStudents.empty()) {
        std::cout << "No students are currently enrolled in " << it->getName() << "\n";
        return;
    }

    std::cout << "Students enrolled in " << it->getName() << ":\n";
    for (const auto* student : enrolledStudents) {
        std::cout << "Name: " << student->getName() 
                  << ", NetID: " << student->getNetID() << "\n";
    }
}

// ----------------------------------------------------------------------
// Post an announcement
void Professor::postAnnouncement() {
    if (coursesTaught.empty()) {
        std::cout << "You are not currently teaching any courses.\n";
        return;
    }

    std::string courseCode = getValidatedInput("Enter the course code: ");
    auto* it = findCourse(courseCode);
    if (!it) {
        std::cout << "You are not teaching a course with the code " << courseCode << "\n";
        return;
    }

    std::string announcement = getValidatedInput("Enter your announcement: ");
    it->addAnnouncement(announcement);
    std::cout << "Announcement posted successfully for course " << courseCode << "\n";
}

// ----------------------------------------------------------------------
// Set office hours
void Professor::setOfficeHours() {
    if (coursesTaught.empty()) {
        std::cout << "You are not currently teaching any courses.\n";
        return;
    }

    std::string courseCode = getValidatedInput("Enter the course code: ");
    auto* it = findCourse(courseCode);
    if (!it) {
        std::cout << "You are not teaching a course with the code " << courseCode << "\n";
        return;
    }

    std::string hours = getValidatedInput("Enter office hours (e.g., 'Tuesdays 2-4 PM'): ");
    it->setOfficeHours(hours);
    std::cout << "Office hours set successfully for course " << courseCode << "\n";
}

// ----------------------------------------------------------------------
// Assign grades
void Professor::assignGrades() {
    if (coursesTaught.empty()) {
        std::cout << "You are not currently teaching any courses.\n";
        return;
    }

    std::string courseCode = getValidatedInput("Enter the course code: ");
    auto* it = findCourse(courseCode);
    if (!it) {
        std::cout << "You are not teaching a course with the code " << courseCode << "\n";
        return;
    }

    const auto& enrolledStudents = it->getEnrolledStudents();
    if (enrolledStudents.empty()) {
        std::cout << "No students are enrolled in " << it->getName() << ".\n";
        return;
    }

    std::string studentNetID = getValidatedInput("Enter the NetID of the student to assign a grade: ");
    auto* studentIt = findStudent(enrolledStudents, studentNetID);
    if (!studentIt) {
        std::cout << "No student with NetID " << studentNetID 
                  << " is enrolled in " << it->getName() << ".\n";
        return;
    }

    // Numeric version with range
    int grade = getValidatedInput<int>("Enter the grade: ", 0, 100);
    studentIt->setGrade(courseCode, it->getName(), grade);
    std::cout << "Grade assigned successfully.\n";
}

// ----------------------------------------------------------------------
// View student grades
void Professor::viewStudentGrades() {
    if (coursesTaught.empty()) {
        std::cout << "You are not currently teaching any courses.\n";
        return;
    }

    std::string courseCode = getValidatedInput("Enter the course code: ");
    auto* it = findCourse(courseCode);
    if (!it) {
        std::cout << "You are not teaching a course with the code " << courseCode << "\n";
        return;
    }

    const auto& enrolledStudents = it->getEnrolledStudents();
    if (enrolledStudents.empty()) {
        std::cout << "No students are enrolled in this course.\n";
        return;
    }

    for (const auto* student : enrolledStudents) {
        auto grades = student->getGrades();
        auto gradeIt = grades.find(courseCode);
        if (gradeIt != grades.end()) {
            std::cout << "Student: " << student->getName()
                      << " (" << student->getNetID() << ") - Grade: "
                      << gradeIt->second.grade << "\n";
        } 
        else {
            std::cout << "Student: " << student->getName() << " - No grade assigned.\n";
        }
    }
}

// ----------------------------------------------------------------------
// Helper: findCourse
Course* Professor::findCourse(const std::string& courseCode) const {
    auto it = std::find_if(
        coursesTaught.begin(),
        coursesTaught.end(),
        [&courseCode](const Course* course) {
            return course->getCourseCode() == courseCode;
        }
    );
    return (it != coursesTaught.end()) ? *it : nullptr;
}

// ----------------------------------------------------------------------
// Helper: findStudent
Student* Professor::findStudent(const std::vector<Student*>& students, const std::string& netID) const {
    auto it = std::find_if(
        students.begin(),
        students.end(),
        [&netID](const Student* student) {
            return student->getNetID() == netID;
        }
    );
    return (it != students.end()) ? *it : nullptr;
}
