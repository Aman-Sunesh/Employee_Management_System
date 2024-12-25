#include <iostream>
#include <vector>
#include <algorithm>
#include "Professor.h"
#include "Course.h"
#include "User.h"
#include "Student.h"
#include "Utility.h"

using namespace std;

// Constructor
Professor::Professor(const string& name, const string& netID, const string& password) : User(name, netID, password) {
    this->name = name;
    this->netID = netID;
    this->password = password;
}

// Returns role
string Professor::getRole() const {
    return "Professor";
}

// Display professor menu
void Professor::displayMenu() {
    do {
        cout << endl;
        cout << "--------------------------------\n";
        cout << "|         Professor Menu       |\n";
        cout << "| 1. View Courses Taught       |\n";
        cout << "| 2. View Students in a Course |\n";
        cout << "| 3. Post Announcements        |\n";
        cout << "| 4. Post Office Hours         |\n";
        cout << "| 5. Assign Grades             |\n";
        cout << "| 6. View Grades of Class      |\n";
        cout << "| 7. Exit                      |\n";
        cout << "--------------------------------\n";

        int choice = getValidatedInput<int>("Enter your choice (1-7): ", 1, 7);

        switch (choice) {
        case 1: viewCourses(); break;
        case 2: viewStudentsInCourse(); break;
        case 3: postAnnouncement(); break;
        case 4: setOfficeHours(); break;
        case 5: assignGrades(); break;
        case 6: viewStudentGrades(); break;
        case 7:
            cout << "Exiting Professor Menu...\n";
            return;
        }
    } while (true);
}

// Getters and setters
string Professor::getName() const { return name; }
string Professor::getNetID() const { return netID; }
string Professor::getDept() const { return department; }
string Professor::getOfficeLoc() const { return officeLocation; }
string Professor::getEmail() const { return email; }
string Professor::getMobile() const { return mobile; }
void Professor::setDepartment(string department) { this->department = department; }
void Professor::setOfficeLocation(string officeLocation) { this->officeLocation = officeLocation; }
void Professor::setEmail(string email) { this->email = email; }
void Professor::setMobile(string mobile) { this->mobile = mobile; }

// Display details
void Professor::displayDetails() {
    cout << endl;
    cout << "Name: " << name << endl;
    cout << "NetID: " << netID << endl;
    cout << "Department: " << department << endl;
    cout << "Email: " << email << endl;
    cout << "Mobile: " << mobile << endl;
    cout << endl;
}

// View courses taught
void Professor::viewCourses() const {
    if (coursesTaught.empty()) {
        cout << "You are not currently teaching any courses.\n";
        return;
    }

    cout << "Courses taught by " << name << ":\n";
    for (const auto* course : coursesTaught) {
        cout << endl;
        cout << "Name: " << course->getName() << endl;
        cout << "Course Code: " << course->getCourseCode() << endl;
        cout << endl;
    }
}

// Add a course
void Professor::addCourseTaught(Course* course) {
    coursesTaught.push_back(course);
}

// View students in a course
void Professor::viewStudentsInCourse() const {
    if (coursesTaught.empty()) {
        cout << "You are not currently teaching any courses.\n";
        return;
    }

    string courseCode = getValidatedInput<string>("Enter the course code: ");
    auto it = findCourse(courseCode);
    if (!it) {
        cout << "You are not teaching a course with the code " << courseCode << endl;
        return;
    }

    const auto& enrolledStudents = (*it)->getEnrolledStudents();
    if (enrolledStudents.empty()) {
        cout << "No students are currently enrolled in " << (*it)->getName() << endl;
        return;
    }

    cout << "Students enrolled in " << (*it)->getName() << ":\n";
    for (const auto* student : enrolledStudents) {
        cout << "Name: " << student->getName() << ", NetID: " << student->getNetID() << endl;
    }
}

// Post an announcement
void Professor::postAnnouncement() {
    if (coursesTaught.empty()) {
        cout << "You are not currently teaching any courses.\n";
        return;
    }

    string courseCode = getValidatedInput<string>("Enter the course code: ");
    auto it = findCourse(courseCode);
    if (!it) {
        cout << "You are not teaching a course with the code " << courseCode << endl;
        return;
    }

    string announcement = getValidatedInput<string>("Enter your announcement: ");
    (*it)->addAnnouncement(announcement);
    cout << "Announcement posted successfully for course " << courseCode << endl;
}

// Set office hours
void Professor::setOfficeHours() {
    if (coursesTaught.empty()) {
        cout << "You are not currently teaching any courses.\n";
        return;
    }

    string courseCode = getValidatedInput<string>("Enter the course code: ");
    auto it = findCourse(courseCode);
    if (!it) {
        cout << "You are not teaching a course with the code " << courseCode << endl;
        return;
    }

    string hours = getValidatedInput<string>("Enter office hours (e.g., 'Tuesdays 2-4 PM'): ");
    (*it)->setOfficeHours(hours);
    cout << "Office hours set successfully for course " << courseCode << endl;
}

// Assign grades
void Professor::assignGrades() {
    if (coursesTaught.empty()) {
        cout << "You are not currently teaching any courses.\n";
        return;
    }

    string courseCode = getValidatedInput<string>("Enter the course code: ");
    auto it = findCourse(courseCode);
    if (!it) {
        cout << "You are not teaching a course with the code " << courseCode << endl;
        return;
    }

    const auto& enrolledStudents = (*it)->getEnrolledStudents();
    if (enrolledStudents.empty()) {
        cout << "No students are enrolled in " << (*it)->getName() << "." << endl;
        return;
    }

    string studentNetID = getValidatedInput<string>("Enter the NetID of the student to assign a grade: ");
    auto studentIt = findStudent(enrolledStudents, studentNetID);
    if (!studentIt) {
        cout << "No student with NetID " << studentNetID << " is enrolled in " << (*it)->getName() << "." << endl;
        return;
    }

    int grade = getValidatedInput<int>("Enter the grade: ", 0, 100);
    (*studentIt)->setGrade(courseCode, (*it)->getName(), grade);
    cout << "Grade assigned successfully.\n";
}

// View student grades
void Professor::viewStudentGrades() {
    if (coursesTaught.empty()) {
        cout << "You are not currently teaching any courses.\n";
        return;
    }

    string courseCode = getValidatedInput<string>("Enter the course code: ");
    auto it = findCourse(courseCode);
    if (!it) {
        cout << "You are not teaching a course with the code " << courseCode << endl;
        return;
    }

    const auto& enrolledStudents = (*it)->getEnrolledStudents();
    if (enrolledStudents.empty()) {
        cout << "No students are enrolled in this course.\n";
        return;
    }

    for (const auto* student : enrolledStudents) {
        auto grades = student->getGrades();
        auto gradeIt = grades.find(courseCode);
        if (gradeIt != grades.end()) {
            cout << "Student: " << student->getName() << " (" << student->getNetID() << ") - Grade: " << gradeIt->second.grade << endl;
        }
        else {
            cout << "Student: " << student->getName() << " - No grade assigned.\n";
        }
    }
}

// Helper to find course
Course* Professor::findCourse(const string& courseCode) const {
    auto it = find_if(coursesTaught.begin(), coursesTaught.end(), [&courseCode](const Course* course) {
        return course->getCourseCode() == courseCode;
        });
    return (it != coursesTaught.end()) ? *it : nullptr;
}

// Helper to find student
Student* Professor::findStudent(const vector<Student*>& students, const string& netID) const {
    auto it = find_if(students.begin(), students.end(), [&netID](const Student* student) {
        return student->getNetID() == netID;
        });
    return (it != students.end()) ? *it : nullptr;
}
