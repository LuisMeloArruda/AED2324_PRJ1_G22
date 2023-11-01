#include "App.h"
#include "Extractor.h"
#include <iostream>
#include <cstdlib>

using namespace std;

App::App(const Extractor &information) {
    this->information = information;
};

int App::run() {
    information.readFiles();
    while (true) {
        int choice = menu();
        int choiceSchedule, choiceStudent;
        string answer;

        switch (choice) {
            case 0:
                return 0;
            case 1:
                choiceSchedule = menuSchedules();
                switch (choiceSchedule) {
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
                if (choiceSchedule != 0) {
                    cout << "\nWanna Continue? [Pressione qualquer tecla para continuar ou 'N' para encerrar]";
                    cin >> answer;
                    if (answer == "N" || answer == "n") return 0;
                }
            break;
            case 2:
                choiceStudent = menuStudents();
                switch (choiceStudent) {
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
                if (choiceStudent != 0) {
                    cout << "\nWanna Continue? [Pressione qualquer tecla para continuar ou 'N' para encerrar]";
                    cin >> answer;
                    if (answer == "N" || answer == "n") return 0;
                }
            break;
            case 3:
                checkStudentsWithNUcs();
                cout << "\nWanna Continue? [Pressione qualquer tecla para continuar ou 'N' para encerrar]";
                cin >> answer;
                if (answer == "N" || answer == "n") return 0;
                break;
            case 4:
                checkTopNStudentsPerUc();
                cout << "\nWanna Continue? [Pressione qualquer tecla para continuar ou 'N' para encerrar]";
                cin >> answer;
                if (answer == "N" || answer == "n") return 0;
                break;
            case 5: {
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
                cout << "\nWanna Continue? [Pressione qualquer tecla para continuar ou 'N' para encerrar]";
                cin >> answer;
                if (answer == "N" || answer == "n") return 0;
                break;
            }
        }
    }
}

int App::menu() {
    system("clear");
    int choice;
    cout << "\nEscolha uma opcao:"
            "\n0. Sair"
            "\n1. Schedules"
            "\n2. Students"
            "\n3. Quantidade de Estudantes com pelo menos N Unidades Curriculares"
            "\n4. Verificar UC's com o maior numero de estudantes"
            "\n5. Novo Pedido\n"
    << "A sua opcao: ";
    cin >> choice;
    if (cin.fail()) {
        throw invalid_argument("Numero invalido");
    }
    while (choice < 0 || choice > 5) {
        system("clear");
        cout << "Opcao invalida. Insira novamente" << endl;
        cin >> choice;
    }
    return choice;
}

int App::menuSchedules() {
    system("clear");
    int choice;
    cout << "\nEscolha uma opcao:"
            "\n0. Go Back"
            "\n1. Schedule of Class"
            "\n2. Schedule of a Student"
            "\n3. Schedule of a Uc\n";
    cin >> choice;
    if (cin.fail()) {
        throw invalid_argument("Numero invalido");
    }
    while (choice < 0 || choice > 3) {
        system("clear");
        cout << "Opcao invalida." << endl;
        cin >> choice;
    }
    return choice;
}


int App::menuStudents() {
    system("clear");
    int choice;
    cout << "\nEscolha uma opcao:"
            "\n0. Go Back"
            "\n1. Class of Students"
            "\n2. Uc of Students"
            "\n3. Year of Students\n";
    cin >> choice;
    if (cin.fail()) {
        throw invalid_argument("Numero invalido");
    }
    while (choice < 0 || choice > 3) {
        system("clear");
        cout << "Opcao invalida." << endl;
        cin >> choice;
    }
    return choice;
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