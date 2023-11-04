#include "Request.h"

/**
 * @brief Constructor of Class Request, it sets Student, targetClass and type attributes to the given ones
 * @details Time complexity: O(1)
 * @param student by reference Student who made the Request
 * @param targetClass by reference Student's desired Class
 * @param type by reference type of the Request
 */
Request::Request(const Student& student, const Class& targetClass, const string& type) {
    this->student = student;
    this->targetClass = targetClass;
    this->type = type;
}

/**
 * @brief Constructor of Class Request if type equals to "S", it sets Student, targetClass and auxClass attributes to the given ones
 * @details Time complexity: O(1)
 * @param student by reference Student who made the Request
 * @param oldClass by reference Student's old Class
 * @param targetClass by reference Student's desired Class
 */
Request::Request(const Student& student, const Class& oldClass, const Class& targetClass) {
    this->student = student;
    this->targetClass = targetClass;
    this->auxClass = oldClass;
    this->type = "S";
}

/**
 * @brief Returns the attribute class Student of Request
 * @details Time complexity: O(1)
 * @return Class Student of Request
 */
Student Request::getStudent() const {
    return student;
}

/**
 * @brief Sets attribute student to the given argument
 * @details Time complexity: O(1)
 * @param student by reference Student to set attribute as
 */
void Request::setStudent(const Student& student) {
    this->student = student;
}

/**
 * @brief Returns the attribute Class targetClass of Request
 * @details Time complexity: O(1)
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
 * @details Time complexity: O(1)
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
 * @details Time complexity: O(1)
 * @return string type of Request
 */
string Request::getType() const {
    return type;
}

void Request::setType(const string& type) {
    this->type = type;
}