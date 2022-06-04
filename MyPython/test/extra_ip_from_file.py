#!/usr/bin/env python

import os
import re

def extra1():
    syslog_servers = []
    syslog_dict = {}

    # conf_file_path = '/etc/rsyslog.conf'
    conf_file_path = './rsyslog.conf'
    line_pattern = '^(\w+\d*|\*).(\*|\w+) +@\[(.+)\]:\d+$'
    ip_pattern = '\d+.\d+.\d+.\d+'
    with open(conf_file_path, 'r') as syslog_file:
        data = syslog_file.readlines()
    pattern_rule = re.compile(pattern = line_pattern)
    for line in data:
        if not pattern_rule.search(line):
            continue
        find_list = re.findall(pattern = ip_pattern, string = line)
        if len(find_list) == 1:
            syslog_servers.append(str(find_list[0]))
    syslog_dict['Syslog Servers'] = syslog_servers

    print('extra1')
    return syslog_dict

# better
def extra2():
    syslog_servers = []
    syslog_dict = {}

    # conf_file_path = '/etc/rsyslog.conf'
    conf_file_path = './rsyslog.conf'
    line_pattern = '^(\w+\d*|\*).(\*|\w+) +@\[(.+)\]:\d+$'
    with open(conf_file_path, 'r') as syslog_file:
        data = syslog_file.read().decode(encoding='utf-8')
    tuples_list = re.findall(pattern = line_pattern, string = data, flags=re.M)
    for tuples in tuples_list:
        if isinstance(tuples, tuple):
            syslog_servers.append(str(tuples[-1]))
    syslog_dict['Syslog Servers'] = syslog_servers

    print('extra2')
    return syslog_dict

def main():
    print(extra1())
    print(extra2())

if __name__ == "__main__":
    main()
