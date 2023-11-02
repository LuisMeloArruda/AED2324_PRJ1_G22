#ifndef AED2324_PRJ1_G22_STUDENT_H
#define AED2324_PRJ1_G22_STUDENT_H

#include <string>
#include <vector>
#include "Class.h"

using namespace std;
/**
 * @brief Class to keep details of a student
 */
class Student{
    private:
        string name;
        string id;
        /** @brief Vector of Class Object with all the classes of a student */
        vector<Class> classes;
    public:
        Student(const string& id, const string& name);
        Student();
        string getId() const;
        void setId(const string& id);
        string getName() const;
        void setName(const string& name);
        vector<Class> getClasses() const;
        void setClasses(const vector<Class>& classes);
        void addClass(const Class& classInfo);
        void removeClass(const Class& classinfo);
        bool operator<(const Student& other) const;
};

#endif //AED2324_PRJ1_G22_STUDENT_H
