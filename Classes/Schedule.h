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
        Schedule(Class classInfo);
        Class getClassInfo() const;
        void setClassInfo(Class classInfo);
        vector<Lesson> getLessons() const;
        void setLessons(vector<Lesson> lessons);
        void addLesson(Lesson lesson);
        set<Student> getStudents() const;
        set<Student>& getStudents();
        void setStudents(set<Student> students);
        void addStudent(Student student);

};

#endif //AED2324_PRJ1_G22_SCHEDULE_H
