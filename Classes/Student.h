#ifndef AED2324_PRJ1_G22_STUDENT_H
#define AED2324_PRJ1_G22_STUDENT_H

#include <string>
#include "Schedule.h"

using namespace std;

class Student{
    private:
        string name;
        unsigned int id;
        Schedule schedule;
    public:
        Student(unsigned int id, string name, Schedule schedule);
        unsigned int getId() const;
        void setId(unsigned  int id);
        string getName() const;
        void setName(string name);
        Schedule getSchedule() const;
        void setSchedule(Schedule schedule);
        bool operator<(const Student& other) const;
        bool operator==(const Student& other) const;
};

#endif //AED2324_PRJ1_G22_STUDENT_H
