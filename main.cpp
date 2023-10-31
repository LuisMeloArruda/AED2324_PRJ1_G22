#include <iostream>
#include "Classes/Extractor.h"

using namespace std;

int main() {

    Extractor information;
    information.readFiles();

    int choice;
    cout << "Escolha uma opcao:\n1. Schedule da Classe\n2. Schedule do Estudante\n3. Schedule da Unidade Curricular\n";
    cout << "4. Estudantes da Classe\n5. Estudantes da UC\n6. Estudantes do Ano\n7. Quantidade de Estudantes com pelo menos N Unidades Curriculares\n8. Novo Pedido\n";
    cout << "9. Processar pedido mais antigo\n";
    cout << "A sua opção: ";

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
    } else if (choice == 4) {
        string classCode;
        int mode;
        cout << "Class Code: ";
        cin >> classCode;
        cout << "Modo de ordenação: ";
        cin >> mode;
        information.getClassStudents(classCode, mode);
    } else if (choice == 5) {
        string ucCode;
        int mode;
        cout << "UC Code: ";
        cin >> ucCode;
        cout << "Modo de ordenação: ";
        cin >> mode;
        information.getUCStudents(ucCode, mode);
    } else if (choice == 6) {
        string year;
        int mode;
        cout << "Year: ";
        cin >> year;
        cout << "Modo de ordenação: ";
        cin >> mode;
        information.getYearStudents(year, mode);
    } else if (choice == 7) {
        int N;
        cout << "Quantas unidades curriculares o estudante deve ter? ";
        cin >> N;
        information.StudentsWithNUc(N);
    } else if (choice == 8) {
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
        }else information.newRequest(studentId, ucCode, classCode, type);
    } else {
        cout << "Opcao invalida." << endl;
    }

    return 0;
}