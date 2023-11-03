#ifndef AED2324_PRJ1_G22_REQUEST_H
#define AED2324_PRJ1_G22_REQUEST_H

#include "Student.h"
/**
 * @brief The class to store details of a given Request
 */
class Request {
    private:
    /** @brief Student Object that keeps Student's information */
        Student student;
    /** @brief  Class Object that contains the attributes of a desired Class */
        Class targetClass;
    /** @brief Class Object that encapsulates the attributes of the old Class */
        Class auxClass;
        /**
         * @brief Type can be:
         * A - Add;
         * R - Remove;
         * S - Switch:
         */
        string type;
    public:
        Request(const Student& student, const Class& targetClass, const string& type);
        Request(const Student& student, const Class& oldClass, const Class& targetClass);
        Student getStudent() const;
        void setStudent(const Student& student);
        Class getTargetClass() const;
        void setTargetClass(const Class& targetClass);
        Class getAuxClass() const;
        void setAuxClass(const Class& auxClass);
        string getType() const;
        void setType(const string& type);
};

#endif //AED2324_PRJ1_G22_REQUEST_H
