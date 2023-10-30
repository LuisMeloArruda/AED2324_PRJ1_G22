#ifndef AED2324_PRJ1_G22_EXTRACTOR_H
#define AED2324_PRJ1_G22_EXTRACTOR_H

#include "Student.h"
#include "Class.h"
#include "Schedule.h"
#include <algorithm>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <iomanip>

class Extractor {
    private:
        set<Student> students;
        vector<Schedule> schedules;
    public:
        Extractor();
        void readFiles();

        // Lookup functions
        void getClassSchedule(string classCode);
        void getStudentSchedule(string id);
        void getUcCodeSchedule(string UcCode);
        void getClassStudents(string classCode, int mode);
        void getUCStudents(string ucCode, int mode);
        void getYearStudents(string year, int mode);

        // Auxiliary Functions
        void readClassesPerUc();
        void readStudentsClasses();
        void readClasses();
        unsigned searchSchedules(Class classInfo);
        static bool studentAlphabetical(Student a, Student b);
        static bool studentNumerical(Student a, Student b);
        void sortAndPrintStudents(vector<Student>& classStudents, int mode);
        string formatedHours(float oldhour);
};

#endif //AED2324_PRJ1_G22_EXTRACTOR_H
