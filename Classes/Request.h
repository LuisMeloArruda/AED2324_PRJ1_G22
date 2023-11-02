#ifndef AED2324_PRJ1_G22_REQUEST_H
#define AED2324_PRJ1_G22_REQUEST_H

#include "Student.h"

class Request {
    private:
        Student student;
        Class targetClass;
        Class auxClass;
        string type;
    public:
        Request(const Student& student, const Class& targetClass, const string& Type);
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
