#ifndef AED2324_PRJ1_G22_CLASS_H
#define AED2324_PRJ1_G22_CLASS_H

#include <string>
#include <set>
#include "Schedule.h"
#include "Student.h"

using namespace std;

class Class{
    private:
        string id;
        Schedule schedule;
        set<Student> students;
    public:
        Class(string id, Schedule schedule);
        string getId() const;
        void setId(string id);
        Schedule getSchedule() const;
        void setSchedule(Schedule schedule);
        Student getStudents() const;
        void addStudent(Student student);
};

#endif //AED2324_PRJ1_G22_CLASS_H
