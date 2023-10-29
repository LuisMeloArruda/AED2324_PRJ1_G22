#include "Schedule.h"

Schedule::Schedule(Class classInfo, vector<Lesson> lessons, set<Student> students) {
    this->classInfo = classInfo;
    this->lessons = lessons;
    this->students = students;
}

Class Schedule::getClassInfo() const {
    return classInfo;
}

void Schedule::setClassInfo(Class classInfo) {
    this->classInfo = classInfo;
}

vector<Lesson> Schedule::getLessons() const {
    return lessons;
}

void Schedule::setLessons(vector<Lesson> lessons) {
    this->lessons = lessons;
}

void Schedule::addLesson(Lesson lesson) {
    lessons.push_back(lesson);
}

set<Student> Schedule::getStudents() const {
    return students;
}

void Schedule::setStudents(set<Student> students) {
    this->students = students;
}
