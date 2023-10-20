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

//A função addStudent do Class.h pedia dois operador para o método .insert(), porém como
//não sei a ordem ideal para o set retorno false. O name é uma boa maneira de ordernar alfabeticamente
bool Student::operator<(const Student &other) const {
    return false;
}

bool Student::operator==(const Student &other) const {
    return false;
}


