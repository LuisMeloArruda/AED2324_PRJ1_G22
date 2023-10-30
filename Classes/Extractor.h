#ifndef AED2324_PRJ1_G22_EXTRACTOR_H
#define AED2324_PRJ1_G22_EXTRACTOR_H

#include "Student.h"
#include "Class.h"
#include "Schedule.h"

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

        // Auxiliary Functions
        void readClassesPerUc();
        void readStudentsClasses();
        void readClasses();
        unsigned searchSchedules(Class classInfo);
        string FormatedHours(float oldhour);
};

#endif //AED2324_PRJ1_G22_EXTRACTOR_H
