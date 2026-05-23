#pragma once

#define DEBUG_VALIDATE(expr)                                                                       \
    do {                                                                                           \
        expr;                                                                                      \
        debug_report_errors(__FILE__, __LINE__);                                                   \
    } while (0)

void debug_report_errors(const char *file, unsigned int line);
