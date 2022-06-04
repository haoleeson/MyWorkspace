#include "logctl_access_redis_wrapper.h"
#include "logctl_access_redis.h"

void* call_get_logctl_subscriber_instance() {
    return LogctlSubscriber::get_instance();
}

void call_initialization(void* instance_ptr, const char* container, const char* process) {
    if (instance_ptr) {
        static_cast<LogctlSubscriber *>(instance_ptr)->initialization(container, process, true, false);
    }
}

int call_get_facility_val(void* instance_ptr) {
    if (instance_ptr) {
        return static_cast<LogctlSubscriber *>(instance_ptr)->get_facility_val();
    }
    return LOGCTL_FACILITY_DEF_VAL;
}

int call_get_loglevel_val(void* instance_ptr) {
    if (instance_ptr) {
        return static_cast<LogctlSubscriber *>(instance_ptr)->get_loglevel_val();
    }
    return LOGCTL_LOGLEVEL_DEF_VAL;
}
