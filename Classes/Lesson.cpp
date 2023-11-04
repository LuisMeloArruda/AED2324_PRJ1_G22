#include "Lesson.h"

/**
 * @brief Constructor of Class Lesson, it sets all the attributes to the given ones
 * @details Time complexity: O(1)
 * @param weekDay by reference day the lesson happens
 * @param start by reference when the lesson starts
 * @param duration by reference time the lesson takes
 * @param type by reference type of the lesson
 */
Lesson::Lesson(const string& weekDay, const float& start, const float& duration, const string& type) {
    this->weekDay = weekDay;
    this->start = start;
    this->duration = duration;
    this->type = type;
}

/**
 * @brief Constructor of Class Lesson, it sets all the attributes to the given ones, in this case
 * the attributes weekDay and duration are in another class Lesson
 * @details Time complexity: O(1)
 * @param baseLesson by reference a class Lesson with the weekDay and duration of Lesson
 * @param start by reference when the Lesson starts
 * @param type by reference type of the Lesson
 */
Lesson::Lesson(const Lesson& baseLesson, const float& start, const string& type) {
    this->weekDay = baseLesson.getWeekDay();
    this->start = start;
    this->duration = baseLesson.getDuration();
    this->type = type;
}

/**
 * @brief Returns the attribute weekDay of a Lesson
 * @details Time complexity: O(1)
 * @return string weekDay of Lesson
 */
string Lesson::getWeekDay() const {
    return weekDay;
}

void Lesson::setWeekDay(const string& weekDay) {
    this->weekDay = weekDay;
}

/**
 * @brief Returns the attribute start of a Lesson
 * @details Time complexity: O(1)
 * @return float start of Lesson
 */
float Lesson::getStart() const {
    return start;
}

void Lesson::setStart(const float& start) {
    this->start = start;
}

/**
 * @brief Returns the attribute duration of a Lesson
 * @details Time complexity: O(1)
 * @return float duration of Lesson
 */
float Lesson::getDuration() const {
    return duration;
}

void Lesson::setDuration(const float& duration) {
    this->duration = duration;
}

/**
 * @brief Returns the attribute type of a Lesson
 * @details Time complexity: O(1)
 * @return string type of Lesson
 */
string Lesson::getType() const {
    return type;
}

void Lesson::setType(const string& type) {
    this->type = type;
}

/**
 * @brief Checks whether one lesson occurs before another or if the lesson type is of lower precedence than the other
 * @details Time complexity: O(1)
 * @param b Lesson to compare
 * @return true if a lesson happens before another, false otherwise
 * if both are in the same time then returns true if type is lower than another, false otherwise
 */
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