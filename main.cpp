#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include "Classes/Schedule.h"
#include "Classes/Lesson.h"
#include "Classes/Student.h"
#include "Classes/Class.h"

using namespace std;

// Função para ler as aulas do arquivo CSV e retornar uma instância de Schedule
Schedule readScheduleFromFile(const string& filename) {
    ifstream file(filename);
    Schedule schedule;

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
    } else {
        string line;
        getline(file, line);  // Ignorar o cabeçalho

        while (getline(file, line)) {
            istringstream ss(line);
            string classCode, ucCode, weekDay, type;
            float start, duration;

            getline(ss, classCode, ',');
            getline(ss, ucCode, ',');
            getline(ss, weekDay, ',');
            ss >> start;
            ss.ignore(1);  // Ignorar a vírgula
            ss >> duration;
            ss.ignore(1);  // Ignorar a vírgula
            getline(ss, type, ',');

            // Instância de Lesson
            Lesson lesson(classCode, ucCode, weekDay, start, duration, type);

            // Adicionar a lesson à instância de Schedule
            schedule.addLesson(lesson);
        }

        file.close();
    }

    return schedule;
}

// Função para associar os estudantes às classes com base no arquivo "students_classes.csv"
/*
void associateStudentsWithClasses(map<string, set<Student>>& classStudents, const string& studentsFilename) {
    ifstream file(studentsFilename);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo de estudantes: " << studentsFilename << endl;
    } else {
        string line;
        getline(file, line);  // Ignorar o cabeçalho

        while (getline(file, line)) {
            istringstream ss(line);
            string studentCode, studentName, ucCode, classCode;

            getline(ss, studentCode, ',');
            getline(ss, studentName, ',');
            getline(ss, ucCode, ',');
            getline(ss, classCode, ',');

            // Crie uma instância de Student
            Student student(studentCode, studentName, Schedule());

            // Associe o estudante à classe usando o ClassCode como chave
            classStudents[classCode].insert(student);
        }

        file.close();
    }
}
*/
// Função para exibir a schedule de uma classe com base no UcCode
void displayClassSchedule(const Schedule& classSchedule) {
    cout << "Digite o UcCode para exibir a schedule da classe: ";
    string inputUcCode;
    cin >> inputUcCode;
    cout << "Schedule da classe com UcCode " << inputUcCode << ":" << endl;

    // Criar um conjunto para rastrear classes já exibidas
    set<string> displayedClasses;

    for (const Lesson& lesson : classSchedule.getLessons()) {
        if (lesson.getUcCode() == inputUcCode) {
            cout << "ClassCode: " << lesson.getClassCode() << " | ";
            cout << "Weekday: " << lesson.getWeekDay() << " | ";
            cout << "Startime: " << lesson.getStart() << " | ";
            cout << "Endtime: " << lesson.getStart() + lesson.getDuration() << " | ";
            cout << "Type: " << lesson.getType() << endl;

            // Adicionar a classe ao conjunto de classes exibidas
            displayedClasses.insert(lesson.getClassCode());

        }
    }

    cout << "-------------------------------------------------------------------------------" << endl;
}


// Função para exibir a schedule de um estudante com base no StudentCode
/*
void displayStudentSchedule(const map<string, set<Student>>& classStudents, const Schedule& classSchedule) {
    cout << "Digite o StudentCode para exibir a schedule do estudante: ";
    string inputStudentCode;
    cin >> inputStudentCode;

    for (const auto& classEntry : classStudents) {
        for (const Student& student : classEntry.second) {
            if (student.getId() == inputStudentCode) {
                cout << "Na UcCode, " << student.getName() << " esta em:" << endl;

                for (const Lesson& lesson : classSchedule.getLessons()) {
                    if (lesson.getClassCode() == classEntry.first) {
                        cout << "ClassCode: " << lesson.getClassCode() << " | ";
                        cout << "Weekday: " << lesson.getWeekDay() << " | ";
                        cout << "Startime: " << lesson.getStart() << " | ";
                        cout << "Endtime: " << lesson.getStart() + lesson.getDuration() << " | ";
                        cout << "Type: " << lesson.getType() << endl;
                    }
                }

                cout << "-------------------------------------------------------------------------------" << endl;
                return;
            }
        }
    }

    cout << "Estudante nao encontrado." << endl;
}
*/
int main() {
    string filename1 = "../data/classes.csv";
    //string filename2 = "../data/students_classes.csv";
    Schedule classSchedule = readScheduleFromFile(filename1);

    //map<string, set<Student>> classStudents;
    //associateStudentsWithClasses(classStudents, filename2);

    int choice;
    cout << "Escolha uma opcao:\n1. Schedule da Classe\n2. Schedule do Estudante\n";
    cin >> choice;

    if (choice == 1) {
        displayClassSchedule(classSchedule);
    } else if (choice == 2) {
       //displayStudentSchedule(classStudents, classSchedule);
    } else {
        cout << "Opcao invalida." << endl;
    }

    return 0;
}