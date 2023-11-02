#ifndef AED2324_PRJ1_G22_LESSON_H
#define AED2324_PRJ1_G22_LESSON_H

#include <string>
#include <map>

using namespace std;

class Lesson{
    private:
        string weekDay;
        float start;
        float duration;
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
