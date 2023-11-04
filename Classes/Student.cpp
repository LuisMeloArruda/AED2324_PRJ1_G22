#include "Student.h"

/**
 * @brief Constructor of class Student, attributes id and name are set to the given ones
 * @details Time complexity: O(1)
 * @param id
 * @param name
 */
Student::Student(const string& id, const string& name) {
    this->id = id;
    this->name = name;
}

/**
 * @brief Standart Constructor of class Student, the attributes id and name are set to "Not Initialized"
 * @details Time complexity: O(1)
 */
Student::Student(){
    this->id = "Not Initialized";
    this->name = "Not Initialized";
}

/**
 * @brief Returns the id of a Student
 * @details Time complexity: O(1)
 * @return string id of Student
 */
string Student::getId() const {
    return id;
}

void Student::setId(const string& id) {
    this->id = id;
}

/**
 * @brief Returns the name of a Student
 * @details Time complexity: O(1)
 * @return string name of Student
 */
string Student::getName() const {
    return name;
}


void Student::setName(const string& name) {
    this->name = name;
}

/**
 * @brief Returns the vector of Classes of the class Student
 * @details Time complexity: O(1)
 * @return vector of classes of Student
 */
vector<Class> Student::getClasses() const{
    return classes;
}

void Student::setClasses(const vector<Class>& classes){
    this->classes = vector<Class>(classes);
}

/**
 * @brief Push back a class in Student's vector of Classes attribute
 * @details Time complexity: O(1)
 * @param classInfo by reference to add in Student's vector of classes
 */
void Student::addClass(const Class& classInfo) {
    classes.push_back(classInfo);
}

/**
 * @brief Find and erase a Class in Student's vector of Classes attribute
 * @details Time complexity: O(n), where "n" is the number of the student's classes
 * @param classInfo by reference to remove from Student's vector of classes
 */
void Student::removeClass(const Class& classInfo) {
    vector<Class> newClassesVector;
    for (const Class& cls: classes) {
        if (cls == classInfo ) continue;
        newClassesVector.push_back(cls);
    }
}

/**
 * @brief Checks if a Student's id is lower than other
 * @details Time complexity: O(1)
 * @param second Student to compare
 * @return True if first student's id is lower that second, false otherwise
 */
bool Student::operator<(const Student& second) const {
    return id < second.id;
}
