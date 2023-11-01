#ifndef AED2324_PRJ1_G22_APP_H
#define AED2324_PRJ1_G22_APP_H

#include "Extractor.h"

class App {
public:
    explicit App(const Extractor &information);

    int run();
    int menu();
    int menuSchedules();
    int menuStudents();


    void checkClassSchedule() const;
    void checkStudentSchedule() const;
    void checkUcSchedule() const;
    void checkClassStudents() const;
    void checkUcStudents() const;
    void checkYearStudents() const;
    void checkStudentsWithNUcs() const;
    void checkTopNStudentsPerUc() const;

private:
    Extractor information;
};

#endif //AED2324_PRJ1_G22_APP_H
