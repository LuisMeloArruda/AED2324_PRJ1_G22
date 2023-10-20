#include "Student.h"

Student::Student(unsigned int id, string name, Schedule schedule) {
    this->id = id;
    this->name = name;
    this->schedule = schedule;
}

unsigned int Student::getId() const {
    return id;
}

void Student::setId(unsigned  int id) {
    this->id = id;
}

string Student::getName() const {
    return name;
}

void Student::setName(string name) {
    this->name = name;
}

Schedule Student::getSchedule() const {
    return schedule;
}

void Student::setSchedule(Schedule schedule) {
    this->schedule = schedule;
}

bool Student::operator<(const Student &other) const {
    return false;
}

bool Student::operator==(const Student &other) const {
    return false;
}


