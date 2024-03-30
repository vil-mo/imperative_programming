#include "logger.h"
#include <stdio.h>
#include <stdarg.h>

FILE *logFile = NULL;
int logCount = 0;

void logSetFile(FILE *file) {
    logFile = file;
}

void logPrintf(const char *format, ...) {
    if (logFile != NULL) {
        logCount++;

        int argc = 0;
        for (int i = 0; format[i] != '\0'; i++) {
            if (format[i] == '%'  && format[i + 1] != '%') {
                argc++;
                i++;
            }
        }
        va_list args;

        va_start(args, argc);

        vfprintf(logFile, format, args);

        va_end(args);
    }
}


int getLogCallsCount() {
    return logCount;
}
