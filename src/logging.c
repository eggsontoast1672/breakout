#include "breakout/logging.h"

#include <stdarg.h>
#include <stdio.h>

void log_message(LogLevel level, const char *fmt, ...) {
    switch (level) {
    case LOG_ERROR: fprintf(stderr, "[ERROR]    "); break;
    case LOG_INFO: fprintf(stderr, "[INFO]     "); break;
    }

    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}
