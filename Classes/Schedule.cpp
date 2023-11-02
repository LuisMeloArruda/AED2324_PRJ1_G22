#include "Schedule.h"

/**
 * @brief Constructor of Class Schedule, set the attribute Class to a given one
 * @details
 * @param classInfo
 */
Schedule::Schedule(const Class& classInfo) {
    this->classInfo = classInfo;
}

/**
 * @brief Returns the attribute Class of the Schedule
 * @details
 * @return Class Object
 */
Class Schedule::getClassInfo() const {
    return classInfo;
}

void Schedule::setClassInfo(const Class& classInfo) {
    this->classInfo = classInfo;
}

/**
 * @brief Returns the attribute vector of Lessons of the Schedule
 * @details
 * @return Vector of Lessons Object
 */
vector<Lesson> Schedule::getLessons() const {
    return lessons;
}

void Schedule::setLessons(const vector<Lesson>& lessons) {
    this->lessons = lessons;
}

/**
 * @brief Push back a lesson in the schedules's vector of lessons attribute
 * @details
 * @param lesson the lesson to add
 */
void Schedule::addLesson(const Lesson& lesson) {
    lessons.push_back(lesson);
}

/**
 * @brief Returns the attribute set of students of the Schedule
 * @details
 * @return Set of Students
 */
set<Student> Schedule::getStudents() const {
    return students;
}

/**
 * @brief Returns by reference the attribute set of students of the Schedule
 * @details
 * @return Set of Students
 */
set<Student>& Schedule::getStudents() {
    return students;
}

void Schedule::setStudents(const set<Student>& students) {
    this->students = students;
}

/**
 * @brief Inserts a student in Schedule's set of Students
 * @details
 * @param student the student to add
 */
void Schedule::addStudent(const Student& student) {
    students.insert(student);
}