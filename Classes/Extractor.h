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
/**
 * @brief class that keeps all information about the Students, Schedules and Requests
 */
class Extractor {
    private:
    /** @brief Set which holds all Students */
        set<Student> students;
        /** @brief Vector to store all Schedules */
        vector<Schedule> schedules;
        /** @brief Queue that keeps all Requests */
        queue<Request> requests;
    public:
        Extractor();
        void readFiles();

        // Lookup Functions
        void getClassSchedule(const string& classCode) const;
        void getStudentSchedule(const string& id) const;
        void getUcCodeSchedule(const string& UcCode) const;
        void getClassStudents(const string& classCode, const int& mode) const;
        void getUCStudents(const string& ucCode, const int& mode) const;
        void getYearStudents(const string& year, const int& mode) const;
        void StudentsWithNUc(const int& N) const;
        void TopNStudentsPerUC(const int& N) const;


        // Request Processing Functions
        void newRequest(const string& studentId, const string& ucCode, const string& classCode, const string& type);
        void newRequest(const string& studentId, const string& oldUcCode, const string& oldClassCode, const string& ucCode, const string& classCode);
        void processRequest();
        void processAllRequests();
        void processAdd(const Request& request);
        void processRemove(const Request& request);
        void processSwitch(const Request& request);

        // Auxiliary Functions
        void readClassesPerUc();
        void readStudentsClasses();
        void readClasses();
        unsigned searchSchedules(const Class& classInfo) const;
        static bool studentAlphabetical(const Student& a, const Student& b);
        static bool studentNumerical(const Student& a, const Student& b);
        static void sortAndPrintStudents(vector<Student>& classStudents, const int& mode) ;
        static string formatedHours(const float& floathour) ;
        bool isSchedulePossible(const Student& student, const Class& newClass);
        bool isSchedulePossible(const Student& student, const Class& newClass, const Class& auxClass);
        bool isBalanceMaintained(const Class& classInfo);
        bool isBalanceMaintained(const Class& classInfo, const Class& auxClass);
        static void addRecord(const Request& request);
};

#endif //AED2324_PRJ1_G22_EXTRACTOR_H
