// Returns the local date/time formatted as 2014-03-19 11:11:52
#include <stdio.h>
FILE* logFile;

char* getFormattedTime(void);
int initLog();
int closeLog();
#define LOG_FILE "log.txt"
// Remove path from filename
#define __SHORT_FILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// Main log macro
#define __LOG__(format, loglevel, ...) printf("%s %-5s [%s] [%s:%d] " format "\n", getFormattedTime(), loglevel, __func__, __SHORT_FILE__, __LINE__, ## __VA_ARGS__)
#define __LOG2__(format, loglevel, ...) fprintf(logFile,"%s %-5s [%s] [%s:%d] " format "\n", getFormattedTime(), loglevel, __func__, __SHORT_FILE__, __LINE__, ## __VA_ARGS__)

// Specific log macros with 
#define LOGDEBUG(format, ...) __LOG__(format, "DEBUG", ## __VA_ARGS__)
#define LOGWARN(format, ...) __LOG__(format, "WARN", ## __VA_ARGS__)
#define LOGERROR(format, ...) __LOG__(format, "ERROR", ## __VA_ARGS__)
#define LOGINFO(format, ...) __LOG2__(format, "INFO", ## __VA_ARGS__)

#define INIT_LOG initLog();
#define CLOSE_LOG closeLog();
