import logging.handlers
import sys
import optparse

#
# sets variable 'optcfg'
#
def get_cmdline_opts():
    optcfg = optparse.OptionParser(usage='usage: %s [--log_facility][--log_level]' % sys.argv[0])
    optcfg.add_option('--log_facility', dest='facility', type='string',
                      default='LOCAL2', help='log control facility')
    optcfg.add_option('--log_level', dest='loglevel', type='string',
                      default='INFO', help='log control level')
    return optcfg.parse_args()

LOGLEVEL_MAP = {
    'EMERG':  logging.CRITICAL,
    'ALERT':  logging.CRITICAL,
    'CRIT':   logging.CRITICAL,
    'ERROR':  logging.ERROR,
    'WARN':   logging.WARN,
    'NOTICE': logging.INFO,
    'INFO':   logging.INFO,
    'DEBUG':  logging.DEBUG,
    'NOTSET': logging.NOTSET
}
LOG_FACILITY_MAP = {
    'KERN':     logging.handlers.SysLogHandler.LOG_KERN,
    'USER':     logging.handlers.SysLogHandler.LOG_USER,
    'MAIL':     logging.handlers.SysLogHandler.LOG_MAIL,
    'DAEMON':   logging.handlers.SysLogHandler.LOG_DAEMON,
    'AUTH':     logging.handlers.SysLogHandler.LOG_AUTH,
    'SYSLOG':   logging.handlers.SysLogHandler.LOG_SYSLOG,
    'LPR':      logging.handlers.SysLogHandler.LOG_LPR,
    'NEWS':     logging.handlers.SysLogHandler.LOG_NEWS,
    'UUCP':     logging.handlers.SysLogHandler.LOG_UUCP,
    'CRON':     logging.handlers.SysLogHandler.LOG_CRON,
    'AUTHPRIV': logging.handlers.SysLogHandler.LOG_AUTHPRIV,
    'FTP':      logging.handlers.SysLogHandler.LOG_FTP,
    'LOCAL0':   logging.handlers.SysLogHandler.LOG_LOCAL0,
    'LOCAL1':   logging.handlers.SysLogHandler.LOG_LOCAL1,
    'LOCAL2':   logging.handlers.SysLogHandler.LOG_LOCAL2,
    'LOCAL3':   logging.handlers.SysLogHandler.LOG_LOCAL3,
    'LOCAL4':   logging.handlers.SysLogHandler.LOG_LOCAL4,
    'LOCAL5':   logging.handlers.SysLogHandler.LOG_LOCAL5,
    'LOCAL6':   logging.handlers.SysLogHandler.LOG_LOCAL6,
    'LOCAL7':   logging.handlers.SysLogHandler.LOG_LOCAL7
}
# convert loglevel string to logging value
def conv_loglevel(loglevel_str):
    """return the map value or default value"""
    if loglevel_str in LOGLEVEL_MAP.keys():
        return LOGLEVEL_MAP[loglevel_str]
    return logging.INFO

# convert facility string to logging value
def conv_facility(facility_str):
    """return the map value or default value"""
    if facility_str in LOG_FACILITY_MAP.keys():
        return LOG_FACILITY_MAP[facility_str]
    return logging.handlers.SysLogHandler.LOG_LOCAL2

def main():
    (opts, args) = get_cmdline_opts()
    log_level = opts.loglevel
    log_facility = opts.facility

    print('The input log level is: ' + log_level + ', the convert val is:' + str(conv_loglevel(log_level)))
    print('The input log facility is: ' + log_facility + ', the convert val is:' + str(conv_facility(log_facility)))


if __name__ == "__main__":
    main()
