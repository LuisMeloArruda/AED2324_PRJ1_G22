#include "Schedule.h"

Schedule::Schedule(vector<Lesson> lessons) {
    this->lessons = lessons;
}


void Schedule::setLessons(vector<Lesson> lessons) {
    this->lessons = lessons;
}


vector<Lesson> Schedule::getLessons() const {
    return lessons;
}

void Schedule::addLesson(Lesson lesson) {
    lessons.push_back(lesson);
}

//A class.cpp pedia um schedule sem argumentos como default então dei alt+enter e apareceu isto
Schedule::Schedule() {}
