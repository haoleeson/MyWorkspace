#ifndef CHANGEBALE_INPUT_PARM_LOG_H
#define CHANGEBALE_INPUT_PARM_LOG_H

#include <iostream>
#include <cstdarg>      // or <stdarg.h> va_start(), va_end()
#include <syslog.h>     // openlog(), vsyslog()

// logctl_log define
#define LOG_TO_SYSLOG       1
#define LOG_TO_STDERR       2
#define LOG_TO_STDOUT       4
#define LOG_IDENT           "logctl"
#define LOG_PRIO_VAL        LOG_NOTICE
#define LOG_FACILITY_VAL    LOG_LOCAL2
#define LOG_OUT_COMPONENT   LOG_TO_SYSLOG

inline void logctl_log(int prio, const char* format_template, ...) {
    if (prio > LOG_PRIO_VAL) {
        return;
    }

    va_list arglist;
    va_start(arglist, format_template);

    if (LOG_OUT_COMPONENT & LOG_TO_SYSLOG) {
        openlog(LOG_IDENT ? LOG_IDENT : "UNKNOWN", LOG_PID, LOG_FACILITY_VAL);
        vsyslog(prio | LOG_FACILITY_VAL, format_template, arglist);
    }

    if (LOG_OUT_COMPONENT & LOG_TO_STDERR) {
        vfprintf(stderr, format_template, arglist);
        fprintf(stderr, "\n");
    }

    if (LOG_OUT_COMPONENT & LOG_TO_STDOUT) {
        vfprintf(stdout, format_template, arglist);
        fprintf(stdout, "\n");
    }

    va_end(arglist);
}

#define logctl_log_error(args...)   logctl_log(LOG_ERR,     ##args)
#define logctl_log_warn(args...)    logctl_log(LOG_WARNING, ##args)
#define logctl_log_notice(args...)  logctl_log(LOG_NOTICE,  ##args)
#define logctl_log_info(args...)    logctl_log(LOG_INFO,    ##args)
#define logctl_log_debug(args...)   logctl_log(LOG_DEBUG,   ##args)

// example main.cpp
//
// int main() {
//     std::string str = "hello world";
//     logctl_log_error("%s", str.c_str());
//     logctl_log_warn("%s", str.c_str());
//     logctl_log_notice("%s", str.c_str());
//     logctl_log_info("%s", str.c_str());
//     logctl_log_debug("%s", str.c_str());
//     return 0;
// }

#endif /* CHANGEBALE_INPUT_PARM_LOG_H */
