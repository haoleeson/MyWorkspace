/**
 * @brief This wrapper file supports other c programs to call logctl(c++).
 * @example gcc main.c -o main -lstdc++ /usr/lib/x86_64-linux-gnu/liblogctlaccessredis.so.0
 */

#ifndef LOGCTL_ACCESS_REDIS_WRAPPER_H
#define LOGCTL_ACCESS_REDIS_WRAPPER_H

#ifdef __cplusplus
extern "C"
{
#endif

void* call_get_logctl_subscriber_instance();
void call_initialization(void* instance_ptr, const char* container, const char* process);
int call_get_facility_val(void* instance_ptr);
int call_get_loglevel_val(void* instance_ptr);

#ifdef __cplusplus
}
#endif

#endif /* LOGCTL_ACCESS_REDIS_WRAPPER_H */
