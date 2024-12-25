#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>

// Forward declaration of Student class
class Student;

using namespace std;

class Course {
private:
    const string name;
    const string courseCode;
    int credits;
    string description;
    string instructor;
    string start_date;
    string end_date;
    string officeHours;
    int numOfStudentsEnrolled;
    vector<Student*> enrolledStudents;
    vector<string> announcements;


public:
    Course();
    Course(const string& name, const string& courseCode, int credits, string description, string start_date, string end_date);

    string getName() const;
    string getCourseCode() const;
    int getCredits() const;
    string getDescription() const;
    string getInstructor() const;
    string getStartDate() const;
    string getEndDate() const;
    int getNumOfStudentsEnrolled() const;

    void setCredits(int credits);
    void setDescription(const string& desc);
    void setInstructor(const string& instr);
    void setStartDate(const string& start);
    void setEndDate(const string& end);

    void incrementEnrollment();
    void decrementEnrollment();

    void addStudent(Student* student);
    void removeStudent(Student* student);
    const vector<Student*>& getEnrolledStudents() const;

    void addAnnouncement(const string& announcement);
    const vector<string>& getAnnouncements() const;

    void setOfficeHours(const string& hours);
    string getOfficeHours() const;

    ~Course();
};

#endif 