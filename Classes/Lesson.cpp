#include "Lesson.h"

Lesson::Lesson(const string& weekDay, const float& start, const float& duration, const string& type) {
    this->weekDay = weekDay;
    this->start = start;
    this->duration = duration;
    this->type = type;
}

Lesson::Lesson(const Lesson& baseLesson, const float& start, const string& type) {
    this->weekDay = baseLesson.getWeekDay();
    this->start = start;
    this->duration = baseLesson.getDuration();
    this->type = type;
}

string Lesson::getWeekDay() const {
    return weekDay;
}

void Lesson::setWeekDay(const string& weekDay) {
    this->weekDay = weekDay;
}

float Lesson::getStart() const {
    return start;
}

void Lesson::setStart(const float& start) {
    this->start = start;
}

float Lesson::getDuration() const {
    return duration;
}

void Lesson::setDuration(const float& duration) {
    this->duration = duration;
}

string Lesson::getType() const {
    return type;
}

void Lesson::setType(const string& type) {
    this->type = type;
}

bool Lesson::operator<(const Lesson& b) const {
    if (weekDay != b.weekDay) {
        map <string, int> daysValue = {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}, {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}, {"Sunday", 7}};
        return daysValue[weekDay] < daysValue[b.weekDay];
    }
    if (start != b.start) return start < b.start;
    if (duration != b.duration) return duration < b.duration;
    if (type != b.type) return type < b.type;
    return false;
}