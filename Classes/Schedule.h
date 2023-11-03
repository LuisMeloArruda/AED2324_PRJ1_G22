#ifndef AED2324_PRJ1_G22_SCHEDULE_H
#define AED2324_PRJ1_G22_SCHEDULE_H

#include "Class.h"
#include "Lesson.h"
#include "Student.h"
#include <vector>
#include <set>

using namespace std;

/**
 * @brief The class which contains the information about a given class, Lessons and Students
 */
class Schedule{
    private:
    /** @brief Class Object that holds schedule's class */
        Class classInfo;
    /** @brief Vector of Lesson Object that keeps the lessons of a schedule */
        vector<Lesson> lessons;
    /** @brief Set of Student Object to store all students with the schedule */
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
