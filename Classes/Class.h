#ifndef AED2324_PRJ1_G22_CLASS_H
#define AED2324_PRJ1_G22_CLASS_H

#include <string>

using namespace std;

class Class{
    private:
        string ucCode;
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
