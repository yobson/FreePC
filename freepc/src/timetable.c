#include "timetable.h"

<<<<<<< HEAD
int periodFromDate() {
    time_t currentTime = time(0);
    printf(time_t);
    return 0;
=======
int getLessonIndex() {
    time_t rawtime;
    struct tm *tminfo;
    int index = 0;
    time (&rawtime);
    tminfo = localtime (&rawtime);
    if (currentWeek > 2 ||
        tminfo->tm_wday > 5 ||
        tminfo->tm_hour > 15 ||
        (tminfo->tm_hour < 8 && tminfo->tm_min < 30)) {
            return 50;
    }
    index += (currentWeek - 1) * 25;
    index += (tminfo->tm_wday - 1) * 5;
    if (tminfo->tm_hour > 9 && tminfo->tm_min > 30) { index++; }
    if (tminfo->tm_hour > 11 && tminfo->tm_min > 10) { index++; }
    if (tminfo->tm_hour > 12 && tminfo->tm_min > 10) { index++; }
    if (tminfo->tm_hour > 14) { index++; }

    return index;
>>>>>>> 86ccf63fa82b89bc3d7af4dae29c65a20eed8199
}