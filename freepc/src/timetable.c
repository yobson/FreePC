#include "timetable.h"

int getLessonIndex() {
    time_t rawtime;
    struct tm *tminfo;
    int index = 0;
    time (&rawtime);
    tminfo = localtime (&rawtime);
    index += (currentWeek - 1) * 25;

    return index;
}