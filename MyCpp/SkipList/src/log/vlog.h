#ifndef VLOG_H
#define VLOG_H

#include <iostream>
#include <cstdarg>          // va_start(), va_end()

#ifdef __linux__
#include <syslog.h>         // openlog(), vsyslog()
#endif

// vlog define
#define LOG_TO_SYSLOG       1
#define LOG_TO_STDERR       2
#define LOG_TO_STDOUT       4

#ifdef __linux__
// Linux、MacOs
#define LOG_IDENT           "my_skip_list"
#define LOG_PRIO_VAL        LOG_DEBUG
#define LOG_FACILITY_VAL    LOG_LOCAL2
#define LOG_OUT_COMP        LOG_TO_STDOUT
#else
// Windows
#define LOG_DEBUG       1
#define LOG_INFO        2
#define LOG_NOTICE      3
#define LOG_WARNING     4
#define LOG_ERR         5
#define LOG_PRIO_VAL    LOG_INFO
#define LOG_OUT_COMP    LOG_TO_STDOUT
#endif

extern void vlog(int prio, const char* format_template, ...);

#define log_error(args...)   vlog(LOG_ERR,     ##args)
#define log_warn(args...)    vlog(LOG_WARNING, ##args)
#define log_notice(args...)  vlog(LOG_NOTICE,  ##args)
#define log_info(args...)    vlog(LOG_INFO,    ##args)
#define log_debug(args...)   vlog(LOG_DEBUG,   ##args)

#endif /* VLOG_H */
