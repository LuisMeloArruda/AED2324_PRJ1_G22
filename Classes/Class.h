#ifndef AED2324_PRJ1_G22_CLASS_H
#define AED2324_PRJ1_G22_CLASS_H

#include <string>

using namespace std;

class Class{
    private:
        string ucCode;
        string classCode;
    public:
        Class(string ucCode, string classCode);
        Class();
        string getUcCode() const;
        void setUcCode(string ucCode);
        string getClassCode() const;
        void setClassCode(string classCode);
        bool operator==(const Class& b);
        bool operator<(const Class& b);
};

#endif //AED2324_PRJ1_G22_CLASS_H
