#include "App.h"
#include "Extractor.h"
#include <iostream>

using namespace std;

App::App(const Extractor &information) {
    this->information = information;
};

int App::run() {
    information.readFiles();
    while (true) {
        int choice = menu();
        switch (choice) {
            case 0:
                return 0;
            case 1:
                checkClassSchedule();
                break;
            case 2:
                checkStudentSchedule();
                break;
            case 3:
                checkUcSchedule();
                break;
            case 4:
                checkClassStudents();
                break;
            case 5:
                checkUcStudents();
                break;
            case 6:
                checkYearStudents();
                break;
            case 7:
                checkStudentsWithNUcs();
                break;
            case 8:
                checkTopNStudentsPerUc();
                break;
            case 9: {
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
                break;
            }
            default:
                cout << "Opcao invalida" << endl;
        }
    }
}

int App::menu() {
    int choice;
    cout << "\nEscolha uma opcao:\n1. Schedule da Classe\n2. Schedule do Estudante\n3. Schedule da Unidade Curricular\n";
    cout << "4. Estudantes da Classe\n5. Estudantes da UC\n6. Estudantes do Ano\n7. Quantidade de Estudantes com pelo menos N Unidades Curriculares\n";
    cout << "8. Verificar UC's com o maior numero de estudantes\n9. Novo Pedido\n0. Sair\n";
    cout << "A sua opcao: ";
    cin >> choice;
    if (cin.fail()) {
        throw invalid_argument("Numero invalido");
    }
    while (choice < 0 || choice > 9) {
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