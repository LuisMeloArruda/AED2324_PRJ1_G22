#ifndef AED2324_PRJ1_G22_APP_H
#define AED2324_PRJ1_G22_APP_H

#include "Extractor.h"

class App {
public:
    explicit App(const Extractor &information);

    // Display functions
    void run();
    static int menu();
    void menuSchedules() const;
    void menuStudents() const;

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
    static bool isValidOption(int choice, int numberOfOptions);
    static bool continueQuestion();
private:
    Extractor information;
};

#endif //AED2324_PRJ1_G22_APP_H
