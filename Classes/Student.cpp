#include "Student.h"
#include <algorithm>

/**
 * @brief Constructor of Class Student, attributes id and name are set to the given ones
 * @details
 * @param id
 * @param name
 */
Student::Student(const string& id, const string& name) {
    this->id = id;
    this->name = name;
}

/**
 * @brief Standart Constructor of Class Student, the attributes id and name are set to "Not Initialized"
 * @details
 */
Student::Student(){
    this->id = "Not Initialized";
    this->name = "Not Initialized";
}

/**
 * @brief Returns the id of a student
 * @details
 * @return string id of Student
 */
string Student::getId() const {
    return id;
}

void Student::setId(const string& id) {
    this->id = id;
}

/**
 * @brief Returns the name of a student
 * @details
 * @return string name of Student
 */
string Student::getName() const {
    return name;
}


void Student::setName(const string& name) {
    this->name = name;
}

/**
 * @brief Returns the vector of classes of a student
 * @details
 * @return vector of classes of Student
 */
vector<Class> Student::getClasses() const{
    return classes;
}

void Student::setClasses(const vector<Class>& classes){
    this->classes = vector<Class>(classes);
}

/**
 * @brief Push back a class in Student's vector of classes attribute
 * @details
 * @param classInfo by reference to add in Student's vector of classes
 */
void Student::addClass(const Class& classInfo) {
    classes.push_back(classInfo);
}

/**
 * @brief Find and erase a class in Student's vector of classes attribute
 * @details
 * @param classInfo by reference to remove from Student's vector of classes
 */
void Student::removeClass(const Class& classInfo) {
    auto newEnd = remove_if(classes.begin(), classes.end(), [&classInfo](const Class& cls)
    {return classInfo == cls;});

    classes.erase(newEnd, classes.end());
}

/**
 * @brief Checks if a Student's id is lower than other
 * @details
 * @param second Student to compare
 * @return True if first student's id is lower that second, false otherwise
 */
bool Student::operator<(const Student& second) const {
    return id < second.id;
}
