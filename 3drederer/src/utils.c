#include <time.h> // time_t, tm, time, localtime, strftime
#include <stdlib.h>
#include "utils.h"




// Returns the local date/time formatted as 2014-03-19 11:11:52
char* getFormattedTime(void) {

    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Must be static, otherwise won't work
    static char _retval[20];
    strftime(_retval, sizeof(_retval), "%Y-%m-%d %H:%M:%S", timeinfo);

    return _retval;
}

int initLog(){

    logFile = fopen(LOG_FILE, "w+");
    if(logFile == NULL) exit(1);
    return 0;


}

int closeLog()
{
    fclose(logFile);
    return 0;
}