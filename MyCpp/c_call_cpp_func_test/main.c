#include <stdio.h>
#include <string.h>
#include <unistd.h>  // sleep
#include "logctl_access_redis_wrapper.h"

//void* g_logctl_sub_instance = NULL;

//void print_log_configuration() {
//    int facility = call_get_facility_val(g_logctl_sub_instance);
//    int loglevel = call_get_loglevel_val(g_logctl_sub_instance);
//    printf("facility = %d\n", facility);
//    printf("loglevel = %d\n", loglevel);
//}

const char* CMD_ERR_NO_MATCH = "NO MATCH";
const char* CMD_SUCCESS = "SUCCESS";

void execute_linux_cmd_pipe(const char* str) {
    printf("%s\n", str);
}

void execute_linux_cmd_pipe_page(const char* str) {
    printf("page: %s\n", str);
}

const char* show_system_log_by_file(const char* argv_0, const char* argv_1, const char* argv_2, const char* argv_3, const char* argv_4)
{
    const char* TAB_LOG_NAME[] = {"auth", "bgpd", "cli", "damon", "kern", "messages", "monit", "sairedis", "swss", "syslog", "teamd", "telemetry", "user", "zebra"};
    const char* TAB_LOG_FILE[] = {"auth.log", "quagga/bgpd.log", "cli.log", "damon.log", "kern.log", "messages", "monit.log", "swss/sairedis.rec", "swss/swss.rec", "syslog", "teamd.log", "telemetry.log", "user.log", "quagga/zebra.log"};
    const char* DEF_SHOW_LOG_CMD = "sudo cat /var/log/%s";
    const char* DEF_SHOW_HISTORY_LOG_CMD = "sudo zgrep '-' /var/log/%s.%s.gz";
    const int len = sizeof(TAB_LOG_NAME) / sizeof(TAB_LOG_NAME[0]);
    const int SYSLOG_INDEX = 9;
    char cmdstr[512] = {0};
    int index = -1;

    if (!argv_0) {
        index = SYSLOG_INDEX;
    } else {
        while (++index < len && strcmp(TAB_LOG_NAME[index], argv_0) != 0);
        if (index == len) {
            return CMD_ERR_NO_MATCH;
        }
    }

    if (!argv_1) {
        snprintf(cmdstr, 512, "sudo cat /var/log/%s", TAB_LOG_FILE[index]);
        execute_linux_cmd_pipe(cmdstr);
        return CMD_SUCCESS;
    }

    if (!argv_2 && strcmp("in-page", argv_1) == 0) {
        snprintf(cmdstr, 512, "sudo cat /var/log/%s", TAB_LOG_FILE[index]);
        execute_linux_cmd_pipe_page(cmdstr);
        return CMD_SUCCESS;
    }

    if (!argv_3 && strcmp("last-rows", argv_1) == 0) {
        snprintf(cmdstr, 512, "sudo cat /var/log/%s | tail -%s", TAB_LOG_FILE[index], argv_2);
        execute_linux_cmd_pipe(cmdstr);
        return CMD_SUCCESS;
    }

    if (!argv_4 && strcmp("history", argv_2) == 0) {
        snprintf(cmdstr, 512, "sudo zgrep '-' /var/log/%s.%s.gz", TAB_LOG_FILE[index], argv_3);
        execute_linux_cmd_pipe_page(cmdstr);
        return CMD_SUCCESS;
    }

    snprintf(cmdstr, 512, "sudo zgrep '-' /var/log/%s.%s.gz | tail -%s", TAB_LOG_FILE[index], argv_4, argv_2);
    execute_linux_cmd_pipe(cmdstr);
    return CMD_SUCCESS;
}


int main(int argc, char* argv[]) {
    const char* str = "hello world";
    printf("%s\n", str);

    show_system_log_by_file(NULL, NULL, NULL, NULL, NULL);
    show_system_log_by_file("auth", NULL, NULL, NULL, NULL);
    show_system_log_by_file("bgpd", NULL, NULL, NULL, NULL);
    show_system_log_by_file("cli", NULL, NULL, NULL, NULL);
    show_system_log_by_file("damon", NULL, NULL, NULL, NULL);
    show_system_log_by_file("kern", NULL, NULL, NULL, NULL);
    show_system_log_by_file("messages", NULL, NULL, NULL, NULL);
    show_system_log_by_file("monit", NULL, NULL, NULL, NULL);
    show_system_log_by_file("sairedis", NULL, NULL, NULL, NULL);
    show_system_log_by_file("swss", NULL, NULL, NULL, NULL);
    show_system_log_by_file("syslog", NULL, NULL, NULL, NULL);
    show_system_log_by_file("teamd", NULL, NULL, NULL, NULL);
    show_system_log_by_file("telemetry", NULL, NULL, NULL, NULL);
    show_system_log_by_file("user", NULL, NULL, NULL, NULL);
    show_system_log_by_file("zebra", NULL, NULL, NULL, NULL);
    show_system_log_by_file("Zebra", NULL, NULL, NULL, NULL);


    show_system_log_by_file("user", "in-page", NULL, NULL, NULL);
    show_system_log_by_file("user", "in-page", "history", "3", NULL);

    show_system_log_by_file("swss", "last-rows", "10", NULL, NULL);
    show_system_log_by_file("swss", "last-rows", "10", "history", "2");



//
//    g_logctl_sub_instance = call_get_logctl_subscriber_instance();
//    const char* container = "teamd";
//    const char* process = "teamd";
//    call_initialization(g_logctl_sub_instance, "teamd", "teamd"); // teamd#teamd
//
//    for (int i = 0; i < 100; ++i) {
//        printf("\n loop time: %d\n", i);
//        print_log_configuration();
//        sleep(3); // 3 S
//    }

    return 0;
}
