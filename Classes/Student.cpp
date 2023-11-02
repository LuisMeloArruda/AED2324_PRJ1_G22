#include "Student.h"
#include <algorithm>

Student::Student(const string& id, const string& name) {
    this->id = id;
    this->name = name;
}

Student::Student(){
    this->id = "Not Initialized";
    this->name = "Not Initialized";
}

string Student::getId() const {
    return id;
}

void Student::setId(const string& id) {
    this->id = id;
}

string Student::getName() const {
    return name;
}

void Student::setName(const string& name) {
    this->name = name;
}

vector<Class> Student::getClasses() const{
    return classes;
}

void Student::setClasses(const vector<Class>& classes){
    this->classes = vector<Class>(classes);
}

void Student::addClass(const Class& classInfo) {
    classes.push_back(classInfo);
}

void Student::removeClass(const Class& classInfo) {
    auto newEnd = remove_if(classes.begin(), classes.end(), [&classInfo](const Class& cls)
    {return classInfo == cls;});

    classes.erase(newEnd, classes.end());
}

bool Student::operator<(const Student& second) const {
    return id < second.id;
}
