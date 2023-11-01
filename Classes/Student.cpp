#include "Student.h"
#include <algorithm>

Student::Student(string id, string name) {
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

void Student::setClasses(vector<Class> classes){
    this->classes = vector<Class>(classes);
}

void Student::addClass(Class classInfo) {
    classes.push_back(classInfo);
}

void Student::removeClass(Class classInfo) {
    auto newEnd = remove_if(classes.begin(), classes.end(), [&classInfo](const Class& cls)
    {return (cls.getUcCode() == classInfo.getUcCode()) && (cls.getClassCode() == classInfo.getClassCode());});

    classes.erase(newEnd, classes.end());
}

bool Student::operator<(const Student& second) const {
    return id < second.id;
}
