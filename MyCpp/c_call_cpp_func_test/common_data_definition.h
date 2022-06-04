#ifndef COMMON_DATA_DEFINITION_H
#define COMMON_DATA_DEFINITION_H

#include <map>
#include <string>
#include <vector>
#include <memory> // std::shared_ptr
#include <algorithm> // std::find()
#include <utility> // std::pair()
#include <stdio.h>
#include <stdarg.h>
#include <syslog.h> // openlog(), vsyslog()

enum LOGCTL_LEVEL
{
    LOGCTL_LEVEL_EMERG  = 0,
    LOGCTL_LEVEL_ALERT  = 1,
    LOGCTL_LEVEL_CRIT   = 2,
    LOGCTL_LEVEL_ERROR  = 3,
    LOGCTL_LEVEL_WARN   = 4,
    LOGCTL_LEVEL_NOTICE = 5,
    LOGCTL_LEVEL_INFO   = 6,
    LOGCTL_LEVEL_DEBUG  = 7
};

enum LOGCTL_FACILITY
{
    /* system facility codes */
    LOGCTL_FACILITY_KERN    = (0 << 3),
    LOGCTL_FACILITY_USER    = (1 << 3),
    LOGCTL_FACILITY_MAIL    = (2 << 3),
    LOGCTL_FACILITY_DAEMON  = (3 << 3),
    LOGCTL_FACILITY_AUTH    = (4 << 3),
    LOGCTL_FACILITY_SYSLOG  = (5 << 3),
    LOGCTL_FACILITY_LPR     = (6 << 3),
    LOGCTL_FACILITY_NEWS    = (7 << 3),
    LOGCTL_FACILITY_UUCP    = (8 << 3),
    LOGCTL_FACILITY_CRON    = (9 << 3),
    LOGCTL_FACILITY_AUTHPRIV = (10 << 3),
    LOGCTL_FACILITY_FTP     = (11 << 3),

    /* reserved facility codes */
    // LOGCTL_FACILITY_NTP     = (12 << 3),
    // LOGCTL_FACILITY_AUDIT   = (13 << 3),
    // LOGCTL_FACILITY_ALERT   = (14 << 3),
    // LOGCTL_FACILITY_CLOCK_DAEMON = (15 << 3),

    /* facility codes reserved for local use */
    LOGCTL_FACILITY_LOCAL0  = (16 << 3),
    LOGCTL_FACILITY_LOCAL1  = (17 << 3),
    LOGCTL_FACILITY_LOCAL2  = (18 << 3),
    LOGCTL_FACILITY_LOCAL3  = (19 << 3),
    LOGCTL_FACILITY_LOCAL4  = (20 << 3),
    LOGCTL_FACILITY_LOCAL5  = (21 << 3),
    LOGCTL_FACILITY_LOCAL6  = (22 << 3),
    LOGCTL_FACILITY_LOCAL7  = (23 << 3)
};

// ANSI CONTROL CODE
#define SET_ATTRIBUTES_HIGHLIGHT    "\033[1m"
#define SET_ATTRIBUTES_DEFAULT      "\033[0m"
#define SET_FRONT_COLOR_BLACK       "\033[30m"
#define SET_FRONT_COLOR_RED         "\033[31m"
#define SET_FRONT_COLOR_GREEN       "\033[32m"
#define SET_FRONT_COLOR_YELLOW      "\033[33m"
#define SET_FRONT_COLOR_BLUE        "\033[34m"
#define SET_FRONT_COLOR_PURPLE      "\033[35m"
#define SET_FRONT_COLOR_LIGHTBLUE   "\033[36m"
#define SET_FRONT_COLOR_WHITE       "\033[37m"
#define SET_FRONT_COLOR_DEFAULT     "\033[39m"

typedef std::vector<std::string> StringVec;
typedef std::pair<std::string, std::string> FieldValueTuple;
#define fvField std::get<0>
#define fvValue std::get<1>

typedef std::tuple<std::string, std::string, std::vector<FieldValueTuple> > KeyOpFieldsValuesTuple;
#define kfvKey    std::get<0>
#define kfvOp     std::get<1>
#define kfvFieldsValues std::get<2>

// logctl -v
#define SHOW_VERSION                "logctl version 0.0.4 (build 2021-11-15)"

// Redis DB index to save log configuration
#define LOGCTL_DB_INDEX             3

// Redis field of keys
#define DB_LOGLEVEL_FIELD           "LOGLEVEL"
#define DB_FACILITY_FIELD           "FACILITY"
#define DB_LOGOUTPUT_FIELD          "LOGOUTPUT"

// default log control configuration
#define DEFAULT_LOGCTL_LOGLEVEL     "WARN"
#define DEFAULT_LOGCTL_FACILITY     "LOCAL2"
#define DEFAULT_LOGCTL_LOGLEVEL_VAL LOGCTL_LEVEL_WARN
#define DEFAULT_LOGCTL_FACILITY_VAL LOGCTL_FACILITY_LOCAL2

#define SELECT_TIMEOUT_MS       1000

// Delimiter of redis key（component）
#define SWSS_DBKEY_DELIMITER    ":"     // swss,    process:process
#define COMMON_DBKEY_DELIMITER  "#"     // other,   container#process

// Interface define
#define VTY_VALUE_WIDTH         12
#define VTY_ENTRY_WIDTH         30
#define VTY_PARAMETER_WIDTH     30
#define INDENT                  "  "
#define ALARM_MESSAGE_COLOR     SET_FRONT_COLOR_RED

extern const std::string g_empty_str;
extern const std::shared_ptr<std::string> g_empty_str_ptr;
extern std::map<std::string, StringVec> g_container_processes_map;

extern bool valid_facility(const std::string& facility);
extern bool valid_loglevel(const std::string& loglevel);
extern bool valid_container(const std::string& container);
extern bool valid_process(const std::string& process, const std::string& container);
extern bool is_swss_key_format(const std::string& container, const std::string& process);
extern int conv_facility_str_2_int(const std::string& facility);
extern int conv_loglevel_str_2_int(const std::string& loglevel);
extern std::string build_redis_key(const std::string& process, const std::string& container, bool b_force_comm = false);
extern bool extract_container_and_process(const std::string& component, std::string& container, std::string& process);

// logctl_log define
#define g_prio_val          LOG_DEBUG
#define g_facility_val      LOG_LOCAL2
#define daemon_log_ident    "logctl"
#define LOG_TO_SYSLOG       1
#define LOG_TO_STDOUT       2
#define LOG_TO_STDERR       4
#define LOG_OUT_COMPONENT   LOG_TO_STDERR

inline void logctl_log(int prio, const char* format_template, ...) {
    if (prio > g_prio_val) {
        return;
    }

    va_list arglist;
    va_start(arglist, format_template);

    if (LOG_OUT_COMPONENT & LOG_TO_SYSLOG) {
        openlog(daemon_log_ident ? daemon_log_ident : "UNKNOWN", LOG_PID, g_facility_val);
        vsyslog(prio | g_facility_val, format_template, arglist);
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

#define COUT_ERROR(msg, ...)     logctl_log(LOG_ERR,        ":- %s: " msg, __FUNCTION__ , ##__VA_ARGS__)
#define COUT_WARN(msg, ...)      logctl_log(LOG_WARNING,    ":- %s: " msg, __FUNCTION__ , ##__VA_ARGS__)
#define COUT_NOTICE(msg, ...)    logctl_log(LOG_NOTICE,     ":- %s: " msg, __FUNCTION__ , ##__VA_ARGS__)
#define COUT_INFO(msg, ...)      logctl_log(LOG_INFO,       ":- %s: " msg, __FUNCTION__ , ##__VA_ARGS__)
#define COUT_DEBUG(msg, ...)     logctl_log(LOG_DEBUG,      ":- %s: " msg, __FUNCTION__ , ##__VA_ARGS__)

#endif /* COMMON_DATA_DEFINITION_H */
