#include "Class.h"

Class::Class(){
    this->ucCode = "Not Initialized";
    this->classCode = "Not Initialized";
}

Class::Class(string ucCode, string classCode) {
    this->ucCode = ucCode;
    this->classCode = classCode;
}

string Class::getClassCode() const {
    return classCode;
}

void Class::setClassCode(string classCode) {
    this->classCode = classCode;
}

string Class::getUcCode() const {
    return ucCode;
}

void Class::setUcCode(string ucCode) {
    this->ucCode = ucCode;
}

bool Class::operator==(const Class& b) {
    return (ucCode==b.ucCode and classCode==b.classCode);
}
bool Class::operator<(const Class& b) {
    return ucCode < b.ucCode || (!(b.ucCode < ucCode) && classCode < b.classCode);
}
