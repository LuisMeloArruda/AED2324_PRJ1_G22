#ifndef AED2324_PRJ1_G22_EXTRACTOR_H
#define AED2324_PRJ1_G22_EXTRACTOR_H

#include "Student.h"
#include "Class.h"
#include "Schedule.h"
#include "Request.h"
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
        queue<Request> requests;
    public:
        Extractor();
        void readFiles();

        // Lookup Functions

        void getClassSchedule(const string &classCode) const;
        void getStudentSchedule(string id) const;
        void getUcCodeSchedule(string UcCode) const;
        void getClassStudents(string classCode, int mode) const;
        void getUCStudents(string ucCode, int mode) const;
        void getYearStudents(string year, int mode) const;
        void StudentsWithNUc(int N) const;
        void TopNStudentsPerUC(int N) const;


        // Request Processing Functions
        void newRequest(string studentId, string ucCode, string classCode, string type);
        void newRequest(string studentId, string oldUcCode, string oldClassCode, string ucCode, string classCode);
        void processRequest();
        void processAdd(Request request);
        void processRemove(Request request);

        // Auxiliary Functions
        void readClassesPerUc();
        void readStudentsClasses();
        void readClasses();
        unsigned searchSchedules(Class classInfo) const;
        static bool studentAlphabetical(Student a, Student b);
        static bool studentNumerical(Student a, Student b);
        void sortAndPrintStudents(vector<Student>& classStudents, int mode) const;
        string formatedHours(float oldhour) const;
        bool isSchedulePossible(Student student, Class newClass);
        bool isBalanceMaintained(Class classInfo);
};

#endif //AED2324_PRJ1_G22_EXTRACTOR_H
