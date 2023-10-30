#include "Request.h"

Request::Request(Student student, Class targetClass, string type) {
    this->student = student;
    this->targetClass = targetClass;
    this->type = type;
}

Request::Request(Student student, Class oldClass, Class targetClass) {
    this->student = student;
    this->targetClass = targetClass;
    this->auxClass = oldClass;
    this->type = "S";
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

Class Request::getAuxClass() const {
    return auxClass;
}

void Request::setAuxClass(Class auxClass) {
    this->auxClass = auxClass;
}

string Request::getType() const {
    return type;
}

void Request::setType(string type) {
    this->type = type;
}