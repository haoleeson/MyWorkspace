import syslog

LOGLEVEL_MAP = {
    'EMERG':  syslog.LOG_EMERG,     # 0
    'ALERT':  syslog.LOG_ALERT,     # 1
    'CRIT':   syslog.LOG_CRIT,      # 2
    'ERROR':  syslog.LOG_ERR,       # 3
    'WARN':   syslog.LOG_WARNING,   # 4
    'NOTICE': syslog.LOG_NOTICE,    # 5
    'INFO':   syslog.LOG_INFO,      # 6
    'DEBUG':  syslog.LOG_DEBUG      # 7
}
LOG_FACILITY_MAP = {
    'KERN':     syslog.LOG_KERN,
    'USER':     syslog.LOG_USER,
    'MAIL':     syslog.LOG_MAIL,
    'DAEMON':   syslog.LOG_DAEMON,
    'AUTH':     syslog.LOG_AUTH,
    'SYSLOG':   syslog.LOG_SYSLOG,
    'LPR':      syslog.LOG_LPR,
    'NEWS':     syslog.LOG_NEWS,
    'UUCP':     syslog.LOG_UUCP,
    'CRON':     syslog.LOG_CRON,
    'LOCAL0':   syslog.LOG_LOCAL0,
    'LOCAL1':   syslog.LOG_LOCAL1,
    'LOCAL2':   syslog.LOG_LOCAL2,
    'LOCAL3':   syslog.LOG_LOCAL3,
    'LOCAL4':   syslog.LOG_LOCAL4,
    'LOCAL5':   syslog.LOG_LOCAL5,
    'LOCAL6':   syslog.LOG_LOCAL6,
    'LOCAL7':   syslog.LOG_LOCAL7
}

SYSLOG_IDENTIFIER = 'test_sys'
g_log_facility = syslog.LOG_LOCAL2
g_log_level = syslog.LOG_INFO
print('g_log_facility is ')
print(g_log_facility)
print('g_log_level is ')
print(g_log_level)
print('syslog.LOG_EMERG is ')
print(syslog.LOG_EMERG)
print('syslog.LOG_ALERT is ')
print(syslog.LOG_ALERT)
print('syslog.LOG_CRIT is ')
print(syslog.LOG_CRIT)
print('syslog.LOG_ERR is ')
print(syslog.LOG_ERR)
print('syslog.LOG_WARNING is ')
print(syslog.LOG_WARNING)
print('syslog.LOG_NOTICE is ')
print(syslog.LOG_NOTICE)
print('syslog.LOG_INFO is ')
print(syslog.LOG_INFO)
print('syslog.LOG_DEBUG is ')
print(syslog.LOG_DEBUG)

def output_mul_logs(msg_str):
    # log_EMERG('EMERGE MSG: ' + msg_str)
    # log_KERN('KERN MSG: ' + msg_str)
    # log_CRON('CRON MSG: ' + msg_str)
    log_error('ERROR MSG: ' + msg_str)
    log_warning('WARNING MSG: ' + msg_str)
    log_info('INFO MSG: ' + msg_str)
    log_debug('DEBUG MSG: ' + msg_str)

def change_facility(log_facility=syslog.LOG_DAEMON):
    syslog.openlog(ident=SYSLOG_IDENTIFIER, logoption=syslog.LOG_PID, facility=log_facility)


def log(prio, msg):
    if prio <= g_log_level:
        syslog.openlog(ident=SYSLOG_IDENTIFIER, facility=g_log_facility)
        syslog.syslog(prio, msg)
        syslog.closelog()

def log_debug(msg):
    log(syslog.LOG_DEBUG, msg)

def log_info(msg):
    log(syslog.LOG_INFO, msg)

def log_warning(msg):
    log(syslog.LOG_WARNING, msg)

def log_error(msg):
    log(syslog.LOG_ERR, msg)


def main1():
    syslog.openlog(ident=SYSLOG_IDENTIFIER, logoption=syslog.LOG_PID, facility=syslog.LOG_DAEMON)
    output_mul_logs('test1')

    change_facility(syslog.LOG_LOCAL2)
    output_mul_logs('test2')

    change_facility(syslog.LOG_LOCAL5)
    output_mul_logs('test3')

def main():
    output_mul_logs('test1')
    output_mul_logs('test2')
    output_mul_logs('test3')

if __name__ == "__main__":
    main()

