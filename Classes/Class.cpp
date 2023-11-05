#include "Class.h"

/**
 * @brief Standard Constructor of class Class, all the attributes are set to "Not Initialized"
 * @details Time complexity: O(1)
 */
Class::Class(){
    this->ucCode = "Not Initialized";
    this->classCode = "Not Initialized";
}

/**
 * @brief Constructor of class Class, all the attributes are set to the given values
 * @details Time complexity: O(1)
 * @param ucCode ID of course unit
 * @param classCode ID of class
 */
Class::Class(const string& ucCode,const string& classCode) {
    this->ucCode = ucCode;
    this->classCode = classCode;
}

/**
 * @brief Returns the ID of class
 * @details Time complexity: O(1)
 * @return The ID of class
 */
string Class::getClassCode() const {
    return classCode;
}

void Class::setClassCode(const string& classCode) {
    this->classCode = classCode;
}

/**
 * @brief Returns the ID of course unit
 * @details Time complexity: O(1)
 * @return The ID of course unit
 */
string Class::getUcCode() const {
    return ucCode;
}

void Class::setUcCode(const string& ucCode) {
    this->ucCode = ucCode;
}

/**
 * @brief Checks if a class is equal to another
 * @details Time complexity: O(1)
 * @param b Class to compare
 * @return true if equal, false otherwise
 */
bool Class::operator==(const Class& b) const {
    return (ucCode==b.ucCode and classCode==b.classCode);
}

/**
 * @brief Checks if a class is lower that another
 * @details Time complexity: O(1)
 * @param b Class to compare
 * @return true if lower, false otherwise
 */
bool Class::operator<(const Class& b) {
    return ucCode < b.ucCode || (!(b.ucCode < ucCode) && classCode < b.classCode);
}
