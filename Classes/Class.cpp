#include "Class.h"

Class::Class(string id, Schedule schedule, set<Student> students) {
    this->id = id;
    this->schedule = schedule;
    this->students = students;
}

string Class::getId() const {
    return id;
}

void Class::setId(string id) {
    this->id = id;
}

Schedule Class::getSchedule() const {
    return schedule;
}

void Class::setSchedule(Schedule schedule) {
    this->schedule = schedule;
}

set<Student> Class::getStudents() const {
    return students;
}

void Class::addStudent(Student student) {
    this->students.insert(student);
}

