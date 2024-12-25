#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <map>
#include "User.h"
#include "Utility.h"

// Forward declarations for external classes used
class Course;
class CourseManager;

using namespace std;


// Struct to hold course grade and name
struct CourseGrade {
    int grade;  // Numeric grade for the course
    string courseName;  // Name of the course
};


// Overload << operator to print CourseGrade objects
ostream& operator<<(ostream& os, const CourseGrade& grade);

// Student class derived from User
class Student : public User
{
private:
    string name;
    string netID;
    string password;
    string level;
    float GPA;
    string email;
    string mobile;

    // Relationships with other classes
    vector<Course*> enrolledCourses;
    CourseManager* C;
    map<string, CourseGrade> courseGrades;


public:
    // Constructors
    Student(const string& name, const string& netID, const string& password);

    // Overridden methods from User
    string getRole() const override;
    void displayMenu() override;

    // Getters and setters
    string getName() const;
    string getNetID() const;
    string getLevel() const;
    float getGPA() const;
    string getEmail() const;
    string getMobile() const;
    void setName(string name);
    void setLevel(string level);
    void setGPA(float GPA);
    void setEmail(string email);
    void setMobile(string mobile);

    // Functionality
    void displayDetails();
    void enrollInCourse();
    void withdrawFromCourse();
    void displayEnrolledCourses() const;
    void displayAvailableCourses() const;
    void setGrade();
    void findGrade() const;
    int getGrade(const string& courseCode) const;
    void viewGPA() const;
    void displayGrades() const;
    void viewCourseAnnouncements() const;
    void viewCourseOfficeHours() const;
    void setGrade(const string& courseCode, const string& courseName, int grade);
    map<string, CourseGrade> getGrades() const;

    void setCourseManager(CourseManager* courseManager);  // Associate a CourseManager

};

#endif 