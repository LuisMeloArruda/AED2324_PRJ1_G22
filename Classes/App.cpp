#include "App.h"
#include "Extractor.h"
#include <iostream>
#include <cstdlib>

using namespace std;

App::App(const Extractor &information) {
    this->information = information;
}

void App::run() {
    information.readFiles();
    while (true) {
        int choice = menu();

        switch (choice) {
            case 0:
                return;
            case 1:
                menuSchedules();
                if (continueQuestion()) return;
                break;
            case 2:
                menuStudents();
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
            }
            case 6: {
                information.processRequest();
                break;
            }
        }
    }
}

int App::menu() {
    system("clear");
    int choice;
    // Print Menu
    cout << "\nEscolha uma opcao:"
            "\n0. Sair"
            "\n1. Schedules"
            "\n2. Students"
            "\n3. Quantidade de Estudantes com pelo menos N Unidades Curriculares"
            "\n4. Verificar UC's com o maior número de estudantes"
            "\n5. Novo Pedido"
            "\n6. Analisar Pedido"
    << "\nA sua opcao: ";
    cin >> choice;

    // Check if option is valid
    while(!isValidOption(choice, 6)) {
        cin >> choice;
    }

    return choice;
}

void App::menuSchedules() const {
    system("clear");
    // Print Menu
    int choice;
    cout << "\nEscolha uma opcao:"
            "\n0. Go Back"
            "\n1. Schedule of Class"
            "\n2. Schedule of a Student"
            "\n3. Schedule of a Uc\n";
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
}

void App::menuStudents() const {
    system("clear");
    int choice;
    // Print Menu
    cout << "\nEscolha uma opcao:"
            "\n0. Go Back"
            "\n1. Class of Students"
            "\n2. Uc of Students"
            "\n3. Year of Students\n";
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
}

void App::checkClassSchedule() const {
    string classCode;
    cout << "Class Code: ";
    cin >> classCode;
    information.getClassSchedule(classCode);
}

void App::checkStudentSchedule() const {
    string id;
    cout << "Student ID: ";
    cin >> id;
    information.getStudentSchedule(id);
}

void App::checkUcSchedule() const {
    string UcCode;
    cout << "Insert UcCode: ";
    cin >> UcCode;
    information.getUcCodeSchedule(UcCode);
}

void App::checkClassStudents() const {
    string classCode;
    int mode;
    cout << "Class Code: ";
    cin >> classCode;
    cout << "Modo de ordenação: ";
    cin >> mode;
    information.getClassStudents(classCode, mode);
}

void App::checkUcStudents() const {
    string ucCode;
    int mode;
    cout << "UC Code: ";
    cin >> ucCode;
    cout << "Modo de ordenação: ";
    cin >> mode;
    information.getUCStudents(ucCode, mode);
}

void App::checkYearStudents() const {
    string year;
    int mode;
    cout << "Year: ";
    cin >> year;
    cout << "Modo de ordenação: ";
    cin >> mode;
    information.getYearStudents(year, mode);
}

void App::checkStudentsWithNUcs() const {
    int N;
    cout << "Quantas unidades curriculares o estudante deve ter? ";
    cin >> N;
    information.StudentsWithNUc(N);
}

void App::checkTopNStudentsPerUc() const {
    int N;
    cout << "Quantas unidades curriculares deseja buscar? \n";
    cin >> N;
    while (N <= 0) {
        cout << "O numero deve ser maior que zero. Digite outra vez: \n";
        cin >> N;
    }
    if (N > 0) {
        information.TopNStudentsPerUC(N);
    }
}

void App::addNewRequest() {
    string studentId, ucCode, classCode, type, oldUcCode, oldClassCode;
    cout << "Action to be taken (A/R/S): ";
    cin >> type;
    cout << "Student ID: ";
    cin >> studentId;
    cout << "UC Code: ";
    cin >> ucCode;
    cout << "Class Code: ";
    cin >> classCode;
    if (type == "S") {
        cout << "UC Code to change: ";
        cin >> oldUcCode;
        cout << "Class Code to change: ";
        cin >> oldClassCode;
        information.newRequest(studentId, oldUcCode, oldClassCode, ucCode, classCode);
    } else information.newRequest(studentId, ucCode, classCode, type);
}

bool App::isValidOption(int choice, int numberOfOptions) {
    if (cin.fail()) {
        throw invalid_argument("Numero invalido");
    }
    if (choice < 0 || choice > numberOfOptions) {
        system("clear");
        cout << "Opcao invalida." << endl;
        return false;
    }
    return true;
}

bool App::continueQuestion() {
    cout << "\nWanna Continue? [S/N]: ";
    string answer;
    cin >> answer;
    if (answer == "N" || answer == "n") return true;
    return false;
}