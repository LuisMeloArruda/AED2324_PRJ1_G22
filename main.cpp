#include <iostream>
#include "Classes/Extractor.h"

using namespace std;

int main() {

    Extractor information;
    information.readFiles();

    int choice;
    cout << "Escolha uma opcao:\n1. Schedule da Classe\n2. Schedule do Estudante\n3. Schedule da Unidade Curricular\n";
    cin >> choice;

    if (choice == 1) {
        string classCode;
        cout << "Class Code: ";
        cin >> classCode;
        information.getClassSchedule(classCode);
    } else if (choice == 2) {
        string id;
        cout << "Student ID: ";
        cin >> id;
        information.getStudentSchedule(id);
    } else if (choice == 3) {
        string UcCode;
        cout << "Insert UcCode: ";
        cin >> UcCode;
        information.getUcCodeSchedule(UcCode);
    } else {
        cout << "Opcao invalida." << endl;
    }

    return 0;
}