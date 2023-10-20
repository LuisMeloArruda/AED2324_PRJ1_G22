#include "Schedule.h"


Schedule::Schedule(set<Lesson> lessons) {
    this->lessons = lessons;
}

set<Lesson> Schedule::getLessons() const {
    return lessons;
}

void Schedule::addLesson(Lesson lesson) {
    lessons.insert(lesson);
}

//A class.cpp pedia um schedule sem argumentos como default então dei alt+enter e apareceu isto
Schedule::Schedule() {}
