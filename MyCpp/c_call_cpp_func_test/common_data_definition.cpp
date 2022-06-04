#include "common_data_definition.h"

const std::string g_empty_str = "";
const std::shared_ptr<std::string> g_empty_str_ptr(new std::string(g_empty_str));

// Loglevel String Value Map
static std::map<std::string, LOGCTL_LEVEL> g_loglevel_map = {
    { "EMERG",  LOGCTL_LEVEL_EMERG },
    { "ALERT",  LOGCTL_LEVEL_ALERT },
    { "CRIT",   LOGCTL_LEVEL_CRIT },
    { "ERROR",  LOGCTL_LEVEL_ERROR },
    { "WARN",   LOGCTL_LEVEL_WARN },
    { "NOTICE", LOGCTL_LEVEL_NOTICE },
    { "INFO",   LOGCTL_LEVEL_INFO },
    { "DEBUG",  LOGCTL_LEVEL_DEBUG }
};

// Facility String Value Map
static std::map<std::string, LOGCTL_FACILITY> g_facility_map = {
    /* system facility codes */
    { "KERN",   LOGCTL_FACILITY_KERN },
    { "USER",   LOGCTL_FACILITY_USER },
    { "MAIL",   LOGCTL_FACILITY_MAIL },
    { "DAEMON", LOGCTL_FACILITY_DAEMON },
    { "AUTH",   LOGCTL_FACILITY_AUTH },
    { "SYSLOG", LOGCTL_FACILITY_SYSLOG },
    { "LPR",    LOGCTL_FACILITY_LPR },
    { "NEWS",   LOGCTL_FACILITY_NEWS },
    { "UUCP",   LOGCTL_FACILITY_UUCP },
    { "CRON",   LOGCTL_FACILITY_CRON },
    { "AUTHPRIV", LOGCTL_FACILITY_AUTHPRIV },
    { "FTP",    LOGCTL_FACILITY_FTP },

    /* reserved facility codes */
    // { "NTP",    LOGCTL_FACILITY_NTP },
    // { "AUDIT",  LOGCTL_FACILITY_AUDIT },
    // { "ALERT",  LOGCTL_FACILITY_ALERT },
    // { "CLOCK_DAEMON", LOGCTL_FACILITY_CLOCK_DAEMON },

    /* facility codes reserved for local use */
    { "LOCAL0", LOGCTL_FACILITY_LOCAL0 },
    { "LOCAL1", LOGCTL_FACILITY_LOCAL1 },
    { "LOCAL2", LOGCTL_FACILITY_LOCAL2 },
    { "LOCAL3", LOGCTL_FACILITY_LOCAL3 },
    { "LOCAL4", LOGCTL_FACILITY_LOCAL4 },
    { "LOCAL5", LOGCTL_FACILITY_LOCAL5 },
    { "LOCAL6", LOGCTL_FACILITY_LOCAL6 },
    { "LOCAL7", LOGCTL_FACILITY_LOCAL7 }
};

// Container and Processes Relation Map ( which allowed log control )
std::map<std::string, StringVec> g_container_processes_map = {
    { "bgp", {
            "bgpcfgd",
            "bgpd",
            "fpmsyncd",
            "staticd",
            "zebra"
    }},
    // { "dhcp_relay", {
    //         "dhcrelay"   // can not support
    // }},
    { "lldp", {
            // "lldpd",     // no use
            "lldpmgrd",
            "lldp_syncd"
    }},
    { "pmon", {
            "hwmgrd"
    }},
    { "radv", {
            "radvd"
            // "radvdump"   // no use
    }},
    // { "sflow", {
    //         "sflowmgrd"  // no use
    // }},
    { "snmp", {
            "snmpd",
            "snmp-subagent"
    }},
    { "swss", {
            "cfgmgrd",
            "fdbmgrd",
            "intmgrd",
            "neighsyncd",
            "orchagent",
            "portsyncd",
            "switchmgrd",
            "transmgrd",
            "vrfmgrd",
            "vxlanmgrd"
    }},
    { "syncd", {
            "linecardd",
            "syncd"
    }},
    { "teamd", {
            "teamd",
            "teammgrd",
            "teamsyncd"
    }}
};

bool valid_facility(const std::string& facility) {
    return g_facility_map.find(facility) != g_facility_map.end();
}

bool valid_loglevel(const std::string& loglevel) {
    return g_loglevel_map.find(loglevel) != g_loglevel_map.end();
}

bool valid_container(const std::string& container) {
    return g_container_processes_map.find(container) != g_container_processes_map.end();
}

// valid the process of container
bool valid_process(const std::string& process, const std::string& container) {
    if (g_container_processes_map.find(container) == g_container_processes_map.end()) {
        return false;
    }
    const StringVec* ptr_vec = &(g_container_processes_map[container]);
    return std::find(ptr_vec->begin(), ptr_vec->end(), process) != ptr_vec->end();
}

int conv_facility_str_2_int(const std::string& facility) {
    std::map<std::string, LOGCTL_FACILITY>::iterator it = g_facility_map.find(facility);
    return (it != g_facility_map.end()) ? g_facility_map[facility] : DEFAULT_LOGCTL_FACILITY_VAL;
}

int conv_loglevel_str_2_int(const std::string& loglevel) {
    std::map<std::string, LOGCTL_LEVEL>::iterator it = g_loglevel_map.find(loglevel);
    return (it != g_loglevel_map.end()) ? g_loglevel_map[loglevel] : DEFAULT_LOGCTL_LOGLEVEL_VAL;
}

bool is_swss_key_format(const std::string& container, const std::string& process) {
    // TODO: sflowmgrd 在 swssloglevel 中不存在（考虑新增 sflowmgrd:sflowmgrd）
    return (container == "swss" || process == "syncd" || process == "linecardd" || process == "fpmsyncd" ||
            process == "hwmgrd" || process == "sflowmgrd" || process == "teammgrd" || process == "teamsyncd");
}

// Gen redis key which associated with COMPONENT
std::string build_redis_key(const std::string& process, const std::string& container, bool b_force_comm) {
    return (b_force_comm || !is_swss_key_format(container, process)) ?
            std::string(container).append(COMMON_DBKEY_DELIMITER).append(process) :
            std::string(process).append(SWSS_DBKEY_DELIMITER).append(process);
}

// Parse component to fill container and process string
bool extract_container_and_process(const std::string& component, std::string& container, std::string& process) {
    int len = component.length();
    if (len <= 0) {
        return false;
    }

    // If it contains the COMMON_DBKEY_DELIMITER, it will be parsed according to the "container#process" rule
    std::size_t common_col_pos = component.find(COMMON_DBKEY_DELIMITER);
    if (common_col_pos != std::string::npos) {
        if (common_col_pos == 0 || common_col_pos == len - 1) {
            return false;
        }
        container = component.substr(0, common_col_pos);
        process = component.substr(common_col_pos + 1, len - 1 - common_col_pos);
        return true;
    }

    // If it contains the SWSS_DBKEY_DELIMITER, it will be parsed according to the "process:process" rule
    std::size_t swss_col_pos = component.find(SWSS_DBKEY_DELIMITER);
    if (swss_col_pos != std::string::npos) {
        if (swss_col_pos == 0 || swss_col_pos == len - 1) {
            return false;
        }
        process = component.substr(swss_col_pos + 1, len - 1 - swss_col_pos);
        return true;
    }
    return false;
}
