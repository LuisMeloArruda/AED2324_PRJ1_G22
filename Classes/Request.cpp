#include "Request.h"

/**
 * @brief Constructor of Class Request, it sets student, targetClass and type attributes to the given ones
 * @details
 * @param student by reference student who made the request
 * @param targetClass by reference student's desired class
 * @param type by reference type of the request
 */
Request::Request(const Student& student, const Class& targetClass, const string& type) {
    this->student = student;
    this->targetClass = targetClass;
    this->type = type;
}

/**
 * @brief Constructor of Class Request if type equals to "S", it sets student, targetClass and auxClass attributes to the given ones
 * @details
 * @param student by reference student who made the request
 * @param oldClass by reference student's old class
 * @param targetClass by reference student's desired class
 */
Request::Request(const Student& student, const Class& oldClass, const Class& targetClass) {
    this->student = student;
    this->targetClass = targetClass;
    this->auxClass = oldClass;
    this->type = "S";
}

/**
 * @brief Returns the attribute Class Student of Request
 * @details
 * @return Class Student of Request
 */
Student Request::getStudent() const {
    return student;
}

void Request::setStudent(const Student& student) {
    this->student = student;
}

/**
 * @brief Returns the attribute Class targetClass of Request
 * @details
 * @return Class Object targetClass of Request
 */
Class Request::getTargetClass() const {
    return targetClass;
}

void Request::setTargetClass(const Class& targetClass) {
    this->targetClass = targetClass;
}

/**
 * @brief Returns the attribute Class auxClass of Request
 * @details
 * @return Class Object auxClass of Request
 */
Class Request::getAuxClass() const {
    return auxClass;
}

void Request::setAuxClass(const Class& auxClass) {
    this->auxClass = auxClass;
}

/**
 * @brief Returns the attribute type of Request
 * @details
 * @return string type of Request
 */
string Request::getType() const {
    return type;
}

void Request::setType(const string& type) {
    this->type = type;
}