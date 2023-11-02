#include "Schedule.h"

Schedule::Schedule(const Class& classInfo) {
    this->classInfo = classInfo;
}

Class Schedule::getClassInfo() const {
    return classInfo;
}

void Schedule::setClassInfo(const Class& classInfo) {
    this->classInfo = classInfo;
}

vector<Lesson> Schedule::getLessons() const {
    return lessons;
}

void Schedule::setLessons(const vector<Lesson>& lessons) {
    this->lessons = lessons;
}

void Schedule::addLesson(const Lesson& lesson) {
    lessons.push_back(lesson);
}

set<Student> Schedule::getStudents() const {
    return students;
}

set<Student>& Schedule::getStudents() {
    return students;
}

void Schedule::setStudents(const set<Student>& students) {
    this->students = students;
}

void Schedule::addStudent(const Student& student) {
    students.insert(student);
}