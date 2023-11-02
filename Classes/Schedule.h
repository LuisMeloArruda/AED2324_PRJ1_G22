#ifndef AED2324_PRJ1_G22_SCHEDULE_H
#define AED2324_PRJ1_G22_SCHEDULE_H

#include "Class.h"
#include "Lesson.h"
#include "Student.h"
#include <vector>
#include <set>

using namespace std;

class Schedule{
    private:
        Class classInfo;
        vector<Lesson> lessons;
        set<Student> students;
    public:
        Schedule(const Class& classInfo);
        Class getClassInfo() const;
        void setClassInfo(const Class& classInfo);
        vector<Lesson> getLessons() const;
        void setLessons(const vector<Lesson>& lessons);
        void addLesson(const Lesson& lesson);
        set<Student> getStudents() const;
        set<Student>& getStudents();
        void setStudents(const set<Student>& students);
        void addStudent(const Student& student);

};

#endif //AED2324_PRJ1_G22_SCHEDULE_H
