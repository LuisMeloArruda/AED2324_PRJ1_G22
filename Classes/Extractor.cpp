#include <fstream>
#include <sstream>
#include <iostream>
#include "Extractor.h"

Extractor::Extractor() {
    this->students = set<Student>();
    this->classes = vector<Class>();
}

void Extractor::readFiles() {
    readClassesPerUc();
}

void Extractor::readClassesPerUc(){
    fstream file("../data/classes_per_uc.csv");
    string line;
    getline(file, line); // Ignorar o cabeçalho

    while (getline(file, line)) {
        istringstream ss(line);
        string ucCode, classCode;
        getline(ss, ucCode, ',');
        getline(ss, classCode, '\n');

        classes.push_back(Class(ucCode, classCode));
    }
}
