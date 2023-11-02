#include "Class.h"

/**
 * @brief Standart Constructor of Class class, all the attributes are set to "Not Initialized"
 * @details
 */
Class::Class(){
    this->ucCode = "Not Initialized";
    this->classCode = "Not Initialized";
}

/**
 * @brief Constructor of Class class, all the attributes are set to the given values
 * @details
 * @param ucCode ID of course unit
 * @param classCode ID of class
 */
Class::Class(const string& ucCode,const string& classCode) {
    this->ucCode = ucCode;
    this->classCode = classCode;
}

/**
 * @brief Returns the ID of class
 * @details
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
 * @details
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
 * @details
 * @param b Class to compare
 * @return true if equal, false otherwise
 */
bool Class::operator==(const Class& b) const {
    return (ucCode==b.ucCode and classCode==b.classCode);
}

/**
 * @brief Checks if a class is lower that another
 * @details
 * @param b Class to compare
 * @return true if lower, false otherwise
 */
bool Class::operator<(const Class& b) {
    return ucCode < b.ucCode || (!(b.ucCode < ucCode) && classCode < b.classCode);
}
