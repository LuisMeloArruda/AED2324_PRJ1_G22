#ifndef AED2324_PRJ1_G22_LESSON_H
#define AED2324_PRJ1_G22_LESSON_H

#include <string>
#include <map>

using namespace std;
/**
 * @brief The class which holds all the necessary information to identify a Lesson
 */
class Lesson{
    private:
        string weekDay;
        float start;
        float duration;
        /** @brief type of a Lesson can be:
         * T - Teórica;
         * P - Prática;
         * PL -  Prática Laboratorial: */
        string type;
    public:
        Lesson(const string& weekDay, const float& start, const float& duration, const string& type);
        Lesson(const Lesson& baseLesson, const float& start, const string& type);
        string getWeekDay() const;
        void setWeekDay(const string& weekDay);
        float getStart() const;
        void setStart(const float& start);
        float getDuration() const;
        void setDuration(const float& duration);
        string getType() const;
        void setType(const string& type);
        bool operator<(const Lesson& b) const;
};

#endif //AED2324_PRJ1_G22_LESSON_H
