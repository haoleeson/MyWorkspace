#include "vlog.h"

void vlog(int prio, const char* format_template, ...) {
    if (prio > LOG_PRIO_VAL) {
        return;
    }

    va_list arglist;
    va_start(arglist, format_template);

    #ifdef __linux__
        if (LOG_OUT_COMP & LOG_TO_SYSLOG) {
            openlog(LOG_IDENT ? LOG_IDENT : "UNKNOWN", LOG_PID, LOG_FACILITY_VAL);
            vsyslog(prio | LOG_FACILITY_VAL, format_template, arglist);
        }
    #endif

    if (LOG_OUT_COMP & LOG_TO_STDERR) {
        vfprintf(stderr, format_template, arglist);
        fprintf(stderr, "\n");
    }
    if (LOG_OUT_COMP & LOG_TO_STDOUT) {
        vfprintf(stdout, format_template, arglist);
        fprintf(stdout, "\n");
    }

    va_end(arglist);
}
