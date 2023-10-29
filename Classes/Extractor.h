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

        //Auxiliary Functions
        void readClassesPerUc();
        void readStudentsClasses();
        unsigned searchSchedules(Class classInfo);
        void testReadStudentClasses();
};

#endif //AED2324_PRJ1_G22_EXTRACTOR_H
