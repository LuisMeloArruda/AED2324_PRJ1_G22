#ifndef AED2324_PRJ1_G22_SCHEDULE_H
#define AED2324_PRJ1_G22_SCHEDULE_H

#include "Lesson.h"
#include <vector>

using namespace std;

class Schedule{
    private:
        vector<Lesson> lessons;
    public:
        Schedule(vector<Lesson> lessons);
        Schedule();
        vector<Lesson> getLessons() const;
        void setLessons(vector<Lesson> lessons) const;
        void addLesson(Lesson lesson);

    void setLessons(vector<Lesson> lessons);
};

#endif //AED2324_PRJ1_G22_SCHEDULE_H
