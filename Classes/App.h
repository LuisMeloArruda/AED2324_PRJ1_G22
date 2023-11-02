#ifndef AED2324_PRJ1_G22_APP_H
#define AED2324_PRJ1_G22_APP_H

#include "Extractor.h"

class App {
public:
    explicit App(const Extractor &information);

    // Display functions
    void run();
    int menu();
    void menuSchedules();
    void menuStudents();

    // Lookup functions
    void checkClassSchedule() const;
    void checkStudentSchedule() const;
    void checkUcSchedule() const;
    void checkClassStudents() const;
    void checkUcStudents() const;
    void checkYearStudents() const;
    void checkStudentsWithNUcs() const;
    void checkTopNStudentsPerUc() const;

    // Request functions
    void addNewRequest();

    // Auxiliary Functions
    bool isValidOption(int choice, int numberOfOptions);
    bool continueQuestion();
private:
    Extractor information;
};

#endif //AED2324_PRJ1_G22_APP_H
