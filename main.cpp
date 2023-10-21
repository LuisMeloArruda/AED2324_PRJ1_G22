#include <iostream>
#include <fstream>
#include <sstream>
#include "Classes/Schedule.h"
#include "Classes/Lesson.h"

using namespace std;

int main() {
    string filename = "../data/classes.csv";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return 1;
    }

    // Ignorar o cabeçalho
    string line;
    getline(file, line);

    // Instância de Schedule para armazenar as lessons
    Schedule schedule;

    // Loop para ler e exibir os blocos com UcCode igual ao input
    cout << "Digite o UcCode para filtrar as lessons: ";
    string inputUcCode;
    cin >> inputUcCode;

    while (getline(file, line)) {
        istringstream ss(line);
        string classCode, ucCode, weekDay, type;
        float start, duration;

        getline(ss, classCode, ',');
        getline(ss, ucCode, ',');
        getline(ss, weekDay, ',');
        ss >> start;
        ss.ignore(1); // Ignorar a vírgula
        ss >> duration;
        ss.ignore(1); // Ignorar a vírgula
        getline(ss, type, ',');

        if (ucCode == inputUcCode) {
            // Instância de Lesson
            Lesson lesson(ucCode, weekDay, start, duration, type);

            // Adicionar a lesson à instância de Schedule
            schedule.addLesson(lesson);

            cout << "UcCode: " << lesson.getUcCode() << " | ";
            cout << "Weekday: " << lesson.getWeekDay() << " | ";
            cout << "Startime: " << lesson.getStart() << " | ";
            cout << "Endtime: " << lesson.getStart() + lesson.getDuration() << " | ";
            cout << "Type: " << lesson.getType() << endl;
        }
    }
    cout << "-------------------------------------------------------------------------------" << endl;

    file.close();

    return 0;
}
