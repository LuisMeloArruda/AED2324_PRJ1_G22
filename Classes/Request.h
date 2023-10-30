#ifndef AED2324_PRJ1_G22_REQUEST_H
#define AED2324_PRJ1_G22_REQUEST_H

#include "Student.h"

class Request {
    private:
        Student student;
        Class targetClass;
        string type;
    public:
        Request(Student student, Class targetClass, string Type);
        Student getStudent() const;
        void setStudent(Student student);
        Class getTargetClass() const;
        void setTargetClass(Class targetClass);
        string getType() const;
        void setType(string type);
};

#endif //AED2324_PRJ1_G22_REQUEST_H
