#include <iostream>
#include "Classes/Extractor.h"

using namespace std;

int main() {

    Extractor information;
    information.readFiles();

    int choice;
    cout << "Escolha uma opcao:\n1. Schedule da Classe\n2. Schedule do Estudante\n";
    cin >> choice;

    if (choice == 1) {
        information.testClassesPerUc();
        //displayClassSchedule(classSchedule);
    } else if (choice == 2) {
       //displayStudentSchedule(classStudents, classSchedule);
    } else {
        cout << "Opcao invalida." << endl;
    }

    return 0;
}