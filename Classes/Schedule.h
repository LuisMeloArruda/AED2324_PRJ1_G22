#ifndef AED2324_PRJ1_G22_SCHEDULE_H
#define AED2324_PRJ1_G22_SCHEDULE_H

#include "Lesson.h"
#include <set>

using namespace std;

class Schedule{
    private:
        set<Lesson> lessons;
    public:
        Schedule(set<Lesson> lessons);
        Schedule();
        set<Lesson> getLessons() const;
        void setLessons(set<Lesson> lessons) const;
        void addLesson(Lesson lesson);

    void setLessons(set<Lesson> lessons);
};

#endif //AED2324_PRJ1_G22_SCHEDULE_H
