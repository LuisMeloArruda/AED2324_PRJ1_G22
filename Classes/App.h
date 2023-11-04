#ifndef AED2324_PRJ1_G22_APP_H
#define AED2324_PRJ1_G22_APP_H

#include "Extractor.h"

/**
 * @brief The class which runs the program
 */
class App {
public:
    explicit App(const Extractor &information);

    // Display functions
    void run();
    static int menu();
    bool menuSchedules() const;
    bool menuStudents() const;
    bool menuProcess();

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
    static void printOrdeningModes();

private:
    /** @brief Extractor object which keeps all students, schedules, requests and their functions */
    Extractor information;
};

#endif //AED2324_PRJ1_G22_APP_H
