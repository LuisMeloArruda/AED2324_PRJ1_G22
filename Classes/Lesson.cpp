#include "Lesson.h"

Lesson::Lesson(string ucCode, string weekDay, float start, float duration, string type) {
    this->ucCode = ucCode;
    this->weekDay = weekDay;
    this->start = start;
    this->duration = duration;
    this->type = type;
}

bool Lesson::operator<(const Lesson& second) const {
    return false;
}

bool Lesson::operator==(const Lesson& second) const {
    return false;
}

string Lesson::getucCode() const {
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