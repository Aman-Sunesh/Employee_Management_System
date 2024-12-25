#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <iostream>
#include <vector>
#include "Course.h"
#include "User.h"

using namespace std;

class Professor : public User
{
private:
    string name;
    string password;
    string netID;
    string department;
    string officeLocation;
    string email;
    string mobile;
    vector<Course*> coursesTaught;

public:
    // Constructor
    Professor(const string& name, const string& netID, const string& password);

    // Overridden methods
    string getRole() const override;
    void displayMenu() override;

    // Getters
    string getName() const;
    string getNetID() const;
    string getDept() const;
    string getOfficeLoc() const;
    string getEmail() const;
    string getMobile() const;
    const vector<Course*>& getCoursesTaught() const;

    // Setters
    void setDepartment(string department);
    void setOfficeLocation(string officeLocation);
    void setEmail(string email);
    void setMobile(string mobile);

    // Functionalities
    void displayDetails();
    void addCourseTaught(Course* course);
    void viewCourses() const;
    void viewStudentsInCourse() const;
    void postAnnouncement();
    void setOfficeHours();
    void assignGrades();
    void viewStudentGrades();

private:
    // Helper functions for modularity
    Course* findCourse(const string& courseCode) const;
    Student* findStudent(const vector<Student*>& students, const string& netID) const;

    // Input validation helper
    template <typename T>
    T getValidatedInput(const string& prompt, T min = T(), T max = T()) const;
};

#endif // PROFESSOR_H
