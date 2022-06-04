//
// Created by lihao52 on 2021/12/9.
//

#ifndef C_DEMO_TEAMD_H
#define C_DEMO_TEAMD_H

#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>

extern const char* daemon_log_ident;

extern int g_prio_val;
extern int g_facility_val;
extern void teamd_log(int prio, const char* format_template, ...);

#define LOG_TO_SYSLOG       1
#define LOG_TO_STDERR       2
#define LOG_TO_STDOUT       4
#define teamd_log_use       LOG_TO_STDOUT

#define teamd_log_err(msg, ...)  teamd_log(LOG_ERR,     ":- %s: " msg, __FUNCTION__ , ##__VA_ARGS__)
#define teamd_log_warn(msg, ...) teamd_log(LOG_WARNING, ":- %s: " msg, __FUNCTION__ , ##__VA_ARGS__)
#define teamd_log_info(msg, ...) teamd_log(LOG_INFO,    ":- %s: " msg, __FUNCTION__ , ##__VA_ARGS__)
#define teamd_log_dbg(msg, ...)  teamd_log(LOG_DEBUG,   ":- %s: " msg, __FUNCTION__ , ##__VA_ARGS__)

#define teamd_log2_err(msg, ...)  teamd_log(LOG_ERR,     ":- logctl: " msg, ##__VA_ARGS__)
#define teamd_log2_warn(msg, ...) teamd_log(LOG_WARNING, ":- logctl: " msg, ##__VA_ARGS__)
#define teamd_log2_info(msg, ...) teamd_log(LOG_INFO,    ":- logctl: " msg, ##__VA_ARGS__)
#define teamd_log2_dbg(msg, ...)  teamd_log(LOG_DEBUG,   ":- logctl: " msg, ##__VA_ARGS__)

#define teamd_log3_err(msg...)  teamd_log(LOG_ERR,     ##msg)
#define teamd_log3_warn(msg...) teamd_log(LOG_WARNING, ##msg)
#define teamd_log3_info(msg...) teamd_log(LOG_INFO,    ##msg)
#define teamd_log3_dbg(msg...)  teamd_log(LOG_DEBUG,   ##msg)

#define teamd_log_dbgx(ctx, val, msg, ...)   \
    if (val <= ctx->debug)                  \
        teamd_log(LOG_DEBUG, ##args)

#endif //C_DEMO_TEAMD_H
