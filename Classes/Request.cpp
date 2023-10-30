#include "Request.h"

Request::Request(Student student, Class targetClass, string type) {
    this->student = student;
    this->targetClass = targetClass;
    this->type = type;
}

Student Request::getStudent() const {
    return student;
}

void Request::setStudent(Student student) {
    this->student = student;
}

Class Request::getTargetClass() const {
    return targetClass;
}

void Request::setTargetClass(Class targetClass) {
    this->targetClass = targetClass;
}

string Request::getType() const {
    return type;
}

void Request::setType(string type) {
    this->type = type;
}