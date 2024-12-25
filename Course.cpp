#include <algorithm>
#include "Course.h"
#include "Student.h"

// Default constructor definition
Course::Course()
    : name(""), courseCode("") {
    credits = -1;
    description = "";
    instructor = "";
    start_date = "";
    end_date = "";
    numOfStudentsEnrolled = 1;
}

// Parameterized constructor definition
Course::Course(const string& name, const string& courseCode, int credits, string description, string start_date, string end_date)
    : name(name), courseCode(courseCode) {
    this->credits = credits;
    this->description = description;
    this->start_date = start_date;
    this->end_date = end_date;
    numOfStudentsEnrolled = 1;
}

// Getter methods
string Course::getName() const
{
    return name;
}

string Course::getCourseCode() const
{
    return courseCode;
}

int Course::getCredits() const
{
    return credits;
}

string Course::getDescription() const
{
    return description;
}

string Course::getInstructor() const
{
    return instructor;
}

string Course::getStartDate() const
{
    return start_date;
}

string Course::getEndDate() const
{
    return end_date;
}

int Course::getNumOfStudentsEnrolled() const
{
    return numOfStudentsEnrolled;
}


// Setter methods
void Course::setCredits(int credits)
{
    this->credits = credits;
}

void Course::setDescription(const string& desc)
{
    description = desc;
}

void Course::setInstructor(const string& instr)
{
    instructor = instr;
}

void Course::setStartDate(const string& start)
{
    start_date = start;
}

void Course::setEndDate(const string& end)
{
    end_date = end;
}

// Student management methods
void Course::incrementEnrollment() {
    numOfStudentsEnrolled++;
}

void Course::decrementEnrollment() {
    if (numOfStudentsEnrolled > 0)
    {
        numOfStudentsEnrolled--;
    }

    else
    {
        cout << "Cannot decrement enrollment; no students are enrolled in this course." << endl;
    }
}


void Course::removeStudent(Student* student) {
    auto it = find(enrolledStudents.begin(), enrolledStudents.end(), student);
    if (it != enrolledStudents.end()) {
        enrolledStudents.erase(it);  // Remove the student from the vector
    }
}

const vector<Student*>& Course::getEnrolledStudents() const
{
    return enrolledStudents;
}

void Course::addAnnouncement(const string& announcement) {
    announcements.push_back(announcement);
}

const vector<string>& Course::getAnnouncements() const {
    return announcements;
}

void Course::setOfficeHours(const string& hours) {
    officeHours = hours;
}

string Course::getOfficeHours() const {
    return officeHours;
}

void Course::addStudent(Student* student) {
    enrolledStudents.push_back(student);
}

Course::~Course() {
}