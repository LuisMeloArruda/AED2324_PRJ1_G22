#include "App.h"
#include "Extractor.h"
#include <iostream>
#include <cstdlib>

using namespace std;

/**
 * @brief Constructor of Class App, it sets the Extractor Object to the given information
 * @param information
 */
App::App(const Extractor &information) {
    this->information = information;
}

/**
 * @brief Method the runs the program, it calls the menu and the read files fuctions
 */
void App::run() {
    information.readFiles();
    while (true) {
        int choice = menu();

        switch (choice) {
            case 0:
                return;
            case 1:
                if (menuSchedules()) break;
                if (continueQuestion()) return;
                break;
            case 2:
                if (menuStudents()) break;
                if (continueQuestion()) return;
                break;
            case 3:
                checkStudentsWithNUcs();
                if (continueQuestion()) return;
                break;
            case 4:
                checkTopNStudentsPerUc();
                if (continueQuestion()) return;
                break;
            case 5: {
                addNewRequest();
                if (continueQuestion()) return;
                break;
            }
            case 6: {
                information.processRequest();
                break;
            }
            case 7: {
                information.PermanentDataChange();
                break;
            }
        }
    }
}

/**
 * @brief Method which prints all the user's possibilities
 * @return user's choice
 */
int App::menu() {
    int choice;
    // Print Menu
    cout << "\nChoose a option:"
            "\n0. Exit"
            "\n1. Schedules"
            "\n2. Students"
            "\n3. The number of students with at least N curriculum units"
            "\n4. Identify the curriculum units with the highest number of students"
            "\n5. New Request"
            "\n6. Process Request"
            "\n7. Permanent data change"
    << "\nYour option: ";
    cin >> choice;

    // Check if option is valid
    while(!isValidOption(choice, 7)) {
        cin >> choice;
    }
    return choice;
}

/**
 * @brief Method which prints possibilities of schedules's menu
 */
bool App::menuSchedules() const {
    // Print Menu
    int choice;
    cout << "\nChoose a option:"
            "\n0. Go Back"
            "\n1. Schedule of Class"
            "\n2. Schedule of a Student"
            "\n3. Schedule of a Uc\n"
            "A sua opção: ";
    cin >> choice;

    // Check if option is valid
    while(!isValidOption(choice, 3)) {
        cin >> choice;
    }

    // Call correct lookup function
    switch (choice) {
        case 0:
            break;
        case 1:
            checkClassSchedule();
            break;
        case 2:
            checkStudentSchedule();
            break;
        case 3:
            checkUcSchedule();
            break;
    }
    return (choice == 0);
}

/**
 * @brief Method which prints possibilities of students's menu
 */
bool App::menuStudents() const {
    int choice;
    // Print Menu
    cout << "\nEscolha uma opcao:"
            "\n0. Go Back"
            "\n1. Class of Students"
            "\n2. Uc of Students"
            "\n3. Year of Students"
            "\nA sua opção: ";
    cin >> choice;

    // Check if option is valid
    while(!isValidOption(choice, 3)) {
        cin >> choice;
    }

    // Call correct lookup function
    switch (choice) {
        case 0:
            break;
        case 1:
            checkClassStudents();
            break;
        case 2:
            checkUcStudents();
            break;
        case 3:
            checkYearStudents();
            break;
    }
    return (choice == 0);
}

/**
 * @brief Asks the user to input the Class's classCode and prints the schedule of that Class
 */
void App::checkClassSchedule() const {
    string classCode;
    cout << "Class Code: ";
    cin >> classCode;
    information.getClassSchedule(classCode);
}

/**
 * @brief Asks the user to input the Student's id and prints the schedule of that Student
 */
void App::checkStudentSchedule() const {
    string id;
    cout << "Student ID: ";
    cin >> id;
    information.getStudentSchedule(id);
}

/**
 * @brief Asks the user to input the course unit's code and prints the schedule of that course unit
 */
void App::checkUcSchedule() const {
    string UcCode;
    cout << "Insert UcCode: ";
    cin >> UcCode;
    information.getUcCodeSchedule(UcCode);
}

/**
 * @brief Asks the user to input Students's classCode, way to sort and then prints the students of that Class
 */
void App::checkClassStudents() const {
    string classCode;
    int mode;
    cout << "Class Code: ";
    cin >> classCode;
    printOrdeningModes();
    cout << "Sorting mode: ";
    cin >> mode;
    while (!isValidOption(mode, 4)) cin >> mode;
    information.getClassStudents(classCode, mode);
}

/**
 * @brief Asks the user to input Students's course unit, way to sort and then prints the students of that course unit
 */
void App::checkUcStudents() const {
    string ucCode;
    int mode;
    cout << "UC Code: ";
    cin >> ucCode;
    printOrdeningModes();
    cout << "Sorting mode: ";
    cin >> mode;
    while (!isValidOption(mode, 4)) cin >> mode;
    information.getUCStudents(ucCode, mode);
}

/**
 * @brief Asks the user to input Students's year, way to sort and then prints the students of that year
 */
void App::checkYearStudents() const {
    string year;
    int mode;
    cout << "Year: ";
    cin >> year;
    printOrdeningModes();
    cout << "Sorting mode: ";
    cin >> mode;
    while (!isValidOption(mode, 4)) cin >> mode;
    information.getYearStudents(year, mode);
}

/**
 * @brief Asks the user to input how many course units the students need to have and then prints
 * the number of students with that many of course units
 */
void App::checkStudentsWithNUcs() const {
    int N;
    cout << "How many course units the student will have? ";
    cin >> N;
    information.StudentsWithNUc(N);
}

/**
 * @brief Asks the user to input how many course units want to know the max number of students
 */
void App::checkTopNStudentsPerUc() const {
    int N;
    cout << "How many course units you want to search? \n";
    cin >> N;
    while (N <= 0) {
        cout << "The number needs to be higher than zero. Try again: \n";
        cin >> N;
    }
    if (N > 0) {
        information.TopNStudentsPerUC(N);
    }
}

/**
 * @brief Asks the user to input type, Student's id, course unit code, class code and them as a Request in queue
 * if type equals to "S" it also asks for old course unit code and old class code
 * @see newRequest(studentId, oldUcCode, oldClassCode, ucCode, classCode)
 * @see newRequest(studentId, ucCode, classCode, type)
 */
void App::addNewRequest() {
    string studentId, ucCode, classCode, type, oldUcCode, oldClassCode;
    cout << "Action to be taken (A/R/S): ";
    cin >> type;
    cout << "Student ID: ";
    cin >> studentId;
    cout << "Destination UC Code: ";
    cin >> ucCode;
    cout << "Destination Class Code: ";
    cin >> classCode;
    if (type == "S") {
        cout << "UC Code to be removed: ";
        cin >> oldUcCode;
        cout << "Class Code to be removed: ";
        cin >> oldClassCode;
        information.newRequest(studentId, oldUcCode, oldClassCode, ucCode, classCode);
    } else information.newRequest(studentId, ucCode, classCode, type);
}

/**
 * @brief Method to test if the given input is within the range of possibilities
 * @details Time complexity: O(1)
 * @param choice user's input
 * @param numberOfOptions range of possibilities
 * @return true if user's input is within range, false otherwise
 */
bool App::isValidOption(int choice, int numberOfOptions) {
    if (cin.fail()) {
        throw invalid_argument("Invalid number");
    }
    if (choice < 0 || choice > numberOfOptions) {
        cout << "Invalid option." << endl;
        return false;
    }
    return true;
}

/**
 * @brief Method asking if the user wants to continue
 * @details Time complexity: O(1)
 * @return true if the user wants to end the program, false otherwise
 */
bool App::continueQuestion() {
    cout << "\nWanna Continue? [Y/N]: ";
    string answer;
    cin >> answer;
    if (answer == "N" || answer == "n") return true;
    return false;
}

/**
 * @brief Method which prints the possibilities to sort a given information
 * @details Time complexity: O(1)
 */
void App::printOrdeningModes() {
    cout << "\nChoose the sorting mode: "
            "\n1. Alphabetically Ascending"
            "\n2. Alphabetically Descending"
            "\n3. Numerically Ascending"
            "\n4. Numerically Descending";
}