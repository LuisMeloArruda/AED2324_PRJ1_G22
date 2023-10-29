#ifndef AED2324_PRJ1_G22_EXTRACTOR_H
#define AED2324_PRJ1_G22_EXTRACTOR_H

#include "Student.h"
#include "Class.h"
#include "Schedule.h"

class Extractor {
    private:
        set<Student> students;
        vector<Class> classes;
    public:
        Extractor();
        void readFiles();
        void readClassesPerUc();
};

#endif //AED2324_PRJ1_G22_EXTRACTOR_H
