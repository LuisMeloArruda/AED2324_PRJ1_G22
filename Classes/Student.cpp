#include "Student.h"

Student::Student(string id, string name, vector<Class>& classes) {
    this->id = id;
    this->name = name;
    this->classes = vector<Class>(classes);
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

vector<Class> Student::getClasses() const{
    return classes;
}

void Student::setClasses(vector<Class> classes) {
    this->classes = vector<Class>(classes);
}


bool Student::operator<(const Student& second) const {
    return id < second.id;
}
