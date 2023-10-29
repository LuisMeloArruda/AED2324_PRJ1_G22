#include "Lesson.h"

Lesson::Lesson(string classCode, string ucCode, string weekDay, float start, float duration, string type) {
    this->classCode = classCode;
    this->ucCode = ucCode;
    this->weekDay = weekDay;
    this->start = start;
    this->duration = duration;
    this->type = type;
}

//A função addLesson do Schedule.h pedia dois operador para o método .insert(), porém como eu
//não sei a ordem ideal para o set retorno false
bool Lesson::operator<(const Lesson& second) const {
    return this->classCode<second.classCode ;
}

bool Lesson::operator==(const Lesson& second) const {
    return second.start == this->start && second.duration == this->duration && second.ucCode == this->ucCode;
}

string Lesson::getClassCode() const {
    return classCode;
}

void Lesson::setClassCode(string classCode) {
    this->classCode = classCode;
}

string Lesson::getUcCode() const {
    return ucCode;
}

void Lesson::setUcCode(string ucCode) {
    this->ucCode = ucCode;
}

string Lesson::getWeekDay() const {
    return weekDay;
}

void Lesson::setWeekDay(string weekDay) {
    this->weekDay = weekDay;
}

float Lesson::getStart() const {
    return start;
}

void Lesson::setStart(float start) {
    this->start = start;
}

float Lesson::getDuration() const {
    return duration;
}

void Lesson::setDuration(float duration) {
    this->duration = duration;
}

string Lesson::getType() const {
    return type;
}

void Lesson::setType(string type) {
    this->type = type;
}