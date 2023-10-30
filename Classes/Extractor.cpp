#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <iomanip>
#include "Extractor.h"

Extractor::Extractor() {
    this->students = set<Student>();
    this->schedules = vector<Schedule>();
}

void Extractor::readFiles() {
    readClassesPerUc();
    readStudentsClasses();
    readClasses();
}

void Extractor::readClassesPerUc() {
    fstream file("../data/classes_per_uc.csv");

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    string line;
    getline(file, line); // Ignorar o cabeçalho

    while (getline(file, line)) {
        // Extracting Info
        istringstream ss(line);
        string ucCode, classCode;
        getline(ss, ucCode, ',');
        getline(ss, classCode);

        schedules.push_back(Schedule(Class(ucCode, classCode)));
    }
}

void Extractor::readStudentsClasses() {
    fstream file("../data/students_classes.csv");

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    string line;
    getline(file, line); // Ignorar o cabeçalho

    while (getline(file, line)) {
        // Extracting Info
        istringstream ss(line);
        string id, name, ucCode, classCode;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, ucCode, ',');
        getline(ss, classCode);
        Student student(id, name);
        Class classInfo(ucCode, classCode);
        student.addClass(classInfo);

        // Placing the info in the students structure
        auto it = students.find(student);
        if (it != students.end()){
            student = *it;
            students.erase(student);
            student.addClass(classInfo);
            students.insert(student);
        }else students.insert(student);

        //Placing the info in the schedules structure
        unsigned index = searchSchedules(classInfo);
        schedules[index].addStudent(student);
    }
}

void Extractor::readClasses() {
    fstream file("../data/classes.csv");

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    string line;
    getline(file, line); // Ignorar o cabeçalho

    while(getline(file, line)) {
        istringstream ss(line);
        string ucCode, classCode, weekDay, type;
        float startHour, duration;

        getline(ss, classCode, ',');
        getline(ss, ucCode, ',');
        getline(ss, weekDay, ',');
        ss >> startHour;
        ss.ignore(1); // Ignorar a vírgula
        ss >> duration;
        ss.ignore(1); // Ignorar a vírgula
        getline(ss, type);

        Class classInfo(ucCode, classCode);
        Lesson lesson(weekDay, startHour, duration, type);
        unsigned index;
        index = searchSchedules(classInfo);
        schedules[index].addLesson(lesson);
    }
}

void Extractor::getClassSchedule(string classCode) {
    map<Lesson, vector<Class>> orderedSchedule;

    for (Schedule schedule: schedules) {
        if (schedule.getClassInfo().getClassCode() == classCode) {
            for (Lesson lesson: schedule.getLessons()) {
                orderedSchedule[lesson].push_back(schedule.getClassInfo());
            }
        }
    }

    cout << "---SCHEDULE---" << endl;
    string currentDay = "";
    for (pair<Lesson, vector<Class>> lesson : orderedSchedule) {
        if (lesson.first.getWeekDay() != currentDay){
            cout << lesson.first.getWeekDay() << ": " << endl;
            currentDay = lesson.first.getWeekDay();
        }
        for (Class classInfo: lesson.second) {
            cout << "START_TIME: " << setw(5) << lesson.first.getStart() << " END_TIME: "
                 << setw(5) << lesson.first.getStart() + lesson.first.getDuration() << " TYPE: "
                 << setw(5) << lesson.first.getType() << " UC_CODE: "
                 << setw(5) << classInfo.getUcCode() << endl;
        }
    }
}

void Extractor::getStudentSchedule(std::string id) {
    auto studentIt = students.find(Student(id, "PlaceHolder"));
    if (studentIt == students.end()) {
        cout << "Student not found!" << endl;
        return;
    }

    map<Lesson, vector<Class>> orderedSchedule;

    for (Class classInfo: studentIt->getClasses()) {
        Schedule schedule = schedules[searchSchedules(classInfo)];
        for (Lesson lesson: schedule.getLessons()) {
            orderedSchedule[lesson].push_back(classInfo);
        }
    }

    cout << "STUDENT_NAME: " << studentIt->getName() << endl;
    cout << "---SCHEDULE---" << endl;
    string currentDay = "";
    for (pair<Lesson, vector<Class>> lesson : orderedSchedule) {
        if (lesson.first.getWeekDay() != currentDay){
            cout << lesson.first.getWeekDay() << ": " << endl;
            currentDay = lesson.first.getWeekDay();
        }
        for (Class classInfo: lesson.second) {
            cout << "START_TIME: " << setw(5) << lesson.first.getStart() << " END_TIME: "
            << setw(5) << lesson.first.getStart() + lesson.first.getDuration() << " TYPE: "
            << setw(5) << lesson.first.getType() << " UC_CODE: " << setw(5) << classInfo.getUcCode()
            << " CLASS_CODE: " << setw(5) << classInfo.getClassCode() << endl;
        }
    }
}

void Extractor::getUcCodeSchedule(string UcCode) {
    map<Lesson, vector<Class>> orderedSchedule;

    for (const Schedule schedule : schedules) {
        if (schedule.getClassInfo().getUcCode() == UcCode) {
            for (const Lesson lesson : schedule.getLessons()) {
                orderedSchedule[lesson].push_back(schedule.getClassInfo());
            }
        }
    }
    if (orderedSchedule.empty()) {
        cout << "Invalid UcCode" << endl;
        return;
    }
    cout << "for UcCode: " << UcCode << endl;
    cout << "---SCHEDULE---" << endl;
    string currentDay = "";
    string hourStart = "";
    string hourEnd = "";
    for (pair<Lesson, vector<Class>> lesson : orderedSchedule) {
        if (lesson.first.getWeekDay() != currentDay){
            cout << "-> " << lesson.first.getWeekDay() << ": " << endl;
            currentDay = lesson.first.getWeekDay();
        }
        hourStart = FormatedHours(lesson.first.getStart());
        hourEnd = FormatedHours(lesson.first.getStart() + lesson.first.getDuration());
        cout << "START_TIME: " << setw(5) << hourStart << " END_TIME: "
             << setw(5) << hourEnd << " TYPE: "
             << setw(5) << lesson.first.getType() << " ClassCode: ";
        for (Class classInfo: lesson.second) {
            cout << classInfo.getClassCode() << " ";
        }
        cout << endl;
    }
}

unsigned Extractor::searchSchedules(Class classInfo) {
    unsigned low = 0, high = schedules.size()-1, middle = high/2;
    while (low <= high) {
        if (schedules[middle].getClassInfo() == classInfo) return middle;
        if (schedules[middle].getClassInfo() < classInfo) low = middle + 1;
        else high = middle - 1;
        middle = (low + high)/2;
    }
    return -1;
}

string Extractor::FormatedHours(float oldhour) {
    int hour = oldhour;
    int minutes = (oldhour - hour) * 60;

    string Pm_Am = "AM";

    ostringstream oss;
    if (hour > 12) {
        hour = hour - 12;
        Pm_Am = "PM";
    }
    oss << hour << ":" << setw(2) << setfill('0') << minutes;
    return oss.str();
}

