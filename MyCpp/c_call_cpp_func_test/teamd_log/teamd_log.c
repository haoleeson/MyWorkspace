//
// Created by lihao52 on 2021/12/9.
//
#include "teamd_log.h"
const char* daemon_log_ident = NULL;

//////////////////

int g_prio_val = LOG_WARNING;
int g_facility_val = LOG_LOCAL2;

void teamd_logv(int prio, const char* format_template, va_list arglist) {
//    int facility_val = call_get_facility_val(g_logctl_sub_instance);
    int facility_val = g_facility_val;

    if (teamd_log_use & LOG_TO_SYSLOG) {
        openlog(daemon_log_ident ? daemon_log_ident : "UNKNOWN", LOG_PID, facility_val);
        vsyslog(prio | facility_val, format_template, arglist);
    }

    if (teamd_log_use & LOG_TO_STDERR) {
        vfprintf(stderr, format_template, arglist);
        fprintf(stderr, "\n");
    }

    if (teamd_log_use & LOG_TO_STDOUT) {
        vfprintf(stdout, format_template, arglist);
        fprintf(stdout, "\n");
    }
}

void teamd_log(int prio, const char* format_template, ...) {
//    int loglevel_val = call_get_loglevel_val(g_logctl_sub_instance);
    int loglevel_val = g_prio_val;

    if (prio > loglevel_val) {
        return;
    }

    va_list arglist;
    va_start(arglist, format_template);
    teamd_logv(prio, format_template, arglist);
    va_end(arglist);
}

