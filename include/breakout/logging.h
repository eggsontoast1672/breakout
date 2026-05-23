#pragma once

typedef enum {
    LOG_ERROR,
    LOG_INFO,
} LogLevel;

void log_message(LogLevel level, const char *fmt, ...);
