#ifndef AED2324_PRJ1_G22_STUDENT_H
#define AED2324_PRJ1_G22_STUDENT_H

#include <string>
#include <vector>
#include "Class.h"

using namespace std;

class Student{
    private:
        string name;
        string id;
        vector<Class> classes;
    public:
        Student(string id, string name);
        Student();
        string getId() const;
        void setId(string id);
        string getName() const;
        void setName(string name);
        vector<Class> getClasses() const;
        void setClasses(vector<Class> classes);
        void addClass(Class classInfo);
        bool operator<(const Student& other) const;
};

#endif //AED2324_PRJ1_G22_STUDENT_H
