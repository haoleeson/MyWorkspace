#include "teamd_log.h"

int main() {
    const char* str = "hello world.";

    teamd_log_err("teamd_log_err %s", str);
    teamd_log_warn("teamd_log_warn %s", str);
    teamd_log_info("teamd_log_info %s", str);
    teamd_log_dbg("teamd_log_dbg %s", str);

    teamd_log2_err("teamd_log2_err %s", str);
    teamd_log2_warn("teamd_log2_warn %s", str);
    teamd_log2_info("teamd_log2_info %s", str);
    teamd_log2_dbg("teamd_log2_dbg %s", str);

    teamd_log3_err("teamd_log3_err %s", str);
    teamd_log3_warn("teamd_log3_warn %s", str);
    teamd_log3_info("teamd_log3_info %s", str);
    teamd_log3_dbg("teamd_log3_dbg %s", str);
    return 0;
}