#include "timetable.h"
#include <time.h>

int periodFromDate() {
    time_t currentTime = time(0);
    printf(ctime(&currentTime));
    return 0;
}