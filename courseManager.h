#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include <iostream>
#include <vector>
#include "Professor.h"

// Forward declaration of UserManager to resolve circular dependency
class UserManager;
class Course;


class CourseManager {
private:
    static CourseManager* instance;
    vector<Course*> courseList;
    UserManager* U; // Pointer to UserManager

    CourseManager() = default; // Make constructor private for singleton pattern

public:
    static CourseManager* getInstance();
    void setUserManager(UserManager* userManager);

    void displayMenu();
    void addCourse();
    void deleteCourse();
    void modifyCourse();
    void assignProfessorToCourse(Course* course);
    void assignProfessorToCourse();
    void viewAllCourses() const;

    const vector<Course*>& getCourses() const;

    ~CourseManager();
};

#endif 