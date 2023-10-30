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
        Lesson(string weekDay, float start, float duration, string type);
        string getWeekDay() const;
        void setWeekDay(string weekDay);
        float getStart() const;
        void setStart(float start);
        float getDuration() const;
        void setDuration(float duration);
        string getType() const;
        void setType(string type);
        bool operator<(Lesson b) const;
};

#endif //AED2324_PRJ1_G22_LESSON_H
