#ifndef AED2324_PRJ1_G22_REQUEST_H
#define AED2324_PRJ1_G22_REQUEST_H

#include "Student.h"
/**
 * @brief Class to store details of a given request
 */
class Request {
    private:
    /** @brief Student Object that keeps student's information */
        Student student;
    /** @brief  Class Object that contains the attributes of a desired class */
        Class targetClass;
    /** @brief Class Object that encapsulates the attributes of the old class */
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
