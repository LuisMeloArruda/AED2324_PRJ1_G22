#include "Student.h"

Student::Student(string id, string name, Schedule schedule) {
    this->id = id;
    this->name = name;
    this->schedule = schedule;
}

string Student::getId() const {
    return id;
}

void Student::setId(string id) {
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
bool Student::operator<(const Student& second) const {
    return name < second.name;
}

bool Student::operator==(const Student& second) const {
    return name == second.name;
}


