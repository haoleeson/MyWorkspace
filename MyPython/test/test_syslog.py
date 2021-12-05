import syslog

def output_mul_logs(msg_str):
    syslog.syslog(syslog.LOG_EMERG, 'EMERGE MSG: ' + msg_str)
    syslog.syslog(syslog.LOG_KERN, 'KERN MSG: ' + msg_str)
    syslog.syslog(syslog.LOG_CRON, 'CRON MSG: ' + msg_str)
    syslog.syslog(syslog.LOG_ERR, 'ERROR MSG: ' + msg_str)
    syslog.syslog(syslog.LOG_WARNING, 'WARNING MSG: ' + msg_str)
    syslog.syslog(syslog.LOG_INFO, 'INFO MSG: ' + msg_str)
    syslog.syslog(syslog.LOG_DEBUG, 'DEBUG MSG: ' + msg_str)
    syslog.closelog()

def change_facility(log_facility=syslog.LOG_DAEMON):
    syslog.openlog(ident="test_syslog", logoption=syslog.LOG_PID, facility=log_facility)

if __name__ == "__main__":
    syslog.openlog(ident="test_syslog.py", logoption=syslog.LOG_PID, facility=syslog.LOG_DAEMON)
    output_mul_logs('test1')

    change_facility(syslog.LOG_LOCAL2)
    output_mul_logs('test2')

    change_facility(syslog.LOG_LOCAL5)
    output_mul_logs('test3')

