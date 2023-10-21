#ifndef AED2324_PRJ1_G22_LESSON_H
#define AED2324_PRJ1_G22_LESSON_H

#include <string>

using namespace std;

class Lesson{
    private:
        string ucCode;
        string weekDay;
        float start;
        float duration;
        string type;
    public:
        Lesson(string ucCode, string weekDay, float start, float duration, string type);
        string getUcCode() const;
        void setUcCode(string ucCode);
        string getWeekDay() const;
        void setWeekDay(string weekDay);
        float getStart() const;
        void setStart(float start);
        float getDuration() const;
        void setDuration(float duration);
        string getType() const;
        void setType(string type);
        bool operator<(const Lesson& other) const;
        bool operator==(const Lesson& other) const;
};

#endif //AED2324_PRJ1_G22_LESSON_H
