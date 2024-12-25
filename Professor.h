#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include "Course.h"
#include "User.h"

// Forward declaration
class Student;

class Professor : public User {
private:
    std::string name;
    std::string password;
    std::string netID;
    std::string department;
    std::string officeLocation;
    std::string email;
    std::string mobile;
    std::vector<Course*> coursesTaught;

public:
    // Constructor
    Professor(const std::string& name, const std::string& netID, const std::string& password);

    // Overridden from User
    std::string getRole() const override;
    void displayMenu() override;

    // Getters
    std::string getName() const;
    std::string getNetID() const;
    std::string getDept() const;
    std::string getOfficeLoc() const;
    std::string getEmail() const;
    std::string getMobile() const;
    const std::vector<Course*>& getCoursesTaught() const { return coursesTaught; }

    // Setters
    void setDepartment(std::string department);
    void setOfficeLocation(std::string officeLocation);
    void setEmail(std::string email);
    void setMobile(std::string mobile);

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
    // Helpers
    Course* findCourse(const std::string& courseCode) const;
    Student* findStudent(const std::vector<Student*>& students, const std::string& netID) const;

    // 1) Overloaded for *numeric* input with a range
    template <typename T>
    T getValidatedInput(const std::string& prompt, T minVal, T maxVal) const;

    // 2) Overload for *string* input (just one argument)
    std::string getValidatedInput(const std::string& prompt) const;
};

#endif // PROFESSOR_H
