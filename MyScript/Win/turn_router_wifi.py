#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import paramiko
from typing import List

def exec_remote_commands(ip, user, pwd: str, commands: List[str]):
  try:
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(ip, 22, user, pwd, timeout=10)
    print("Login %s success\n" % ip)

    for command in commands:
        print("\texec: %s\n" % command)
        stdin, stdout, stderr = ssh.exec_command(command)
        # stdin.write("Y")
        out = stdout.readlines()
        for o in out:
            print(o)
    ssh.close()
  except:
    print("%s\tError\n" % ip)


def login_router_exec_commands(commands: List[str]):
    ip = 'your_ip'
    user = 'your_user_name'
    pwd = 'your_password'
    exec_remote_commands(ip, user, pwd, commands)


def main():
    input_str = 'up'
    if len(sys.argv) > 1:
        input_str = sys.argv[1]
    commands: List[str] = []

    if input_str == 'up':
        commands.append('/sbin/ifconfig wlan1 up')
    elif input_str == 'down':
        commands.append('/sbin/ifconfig wlan1 down')
    else:
        print("the input str '%s' not support" % input_str)
        return 1
    login_router_exec_commands(commands)


if __name__=='__main__':
    main()
