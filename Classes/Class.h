#ifndef AED2324_PRJ1_G22_CLASS_H
#define AED2324_PRJ1_G22_CLASS_H

#include <string>

using namespace std;

/**
 * @brief class that stores data about a given class in a course unit
 */
class Class{
    private:
    /** @brief ID of a course unit */
        string ucCode;
    /** @brief ID of a class */
        string classCode;
    public:
        Class(const string& ucCode, const string& classCode);
        Class();
        string getClassCode() const;
        void setClassCode(const string& classCode);
        string getUcCode() const;
        void setUcCode(const string& ucCode);
        bool operator==(const Class& b) const;
        bool operator<(const Class& b);
};

#endif //AED2324_PRJ1_G22_CLASS_H
