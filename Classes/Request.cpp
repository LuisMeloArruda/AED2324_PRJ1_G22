#include "Request.h"

Request::Request(const Student& student, const Class& targetClass, const string& type) {
    this->student = student;
    this->targetClass = targetClass;
    this->type = type;
}

Request::Request(const Student& student, const Class& oldClass, const Class& targetClass) {
    this->student = student;
    this->targetClass = targetClass;
    this->auxClass = oldClass;
    this->type = "S";
}

Student Request::getStudent() const {
    return student;
}

void Request::setStudent(const Student& student) {
    this->student = student;
}

Class Request::getTargetClass() const {
    return targetClass;
}

void Request::setTargetClass(const Class& targetClass) {
    this->targetClass = targetClass;
}

Class Request::getAuxClass() const {
    return auxClass;
}

void Request::setAuxClass(const Class& auxClass) {
    this->auxClass = auxClass;
}

string Request::getType() const {
    return type;
}

void Request::setType(const string& type) {
    this->type = type;
}