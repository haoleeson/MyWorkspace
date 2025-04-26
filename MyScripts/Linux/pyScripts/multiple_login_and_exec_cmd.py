#!/opt/homebrew/bin/python3

import os
import string
import paramiko
from typing import List
from datetime import datetime


DEFAULT_USER = 'root'
DEFAULT_PWD = '********'
DEVICE_LIST_FILE = '/Users/haoleeson/code/myPython/multiple_login_device.csv'
# EXEC_COMMANDS = ['uname -a', 'echo $HOSTNAME']
# EXEC_COMMANDS = ['docker exec -i pmon ls -l /proc/26/task/ | tail -n +2']
# 批量对 HBHLLAB 设备执行热补丁
# EXEC_COMMANDS = ['./sonic-OS-p4gw201911-1.0.0.patch install', '/var/patches/hotfixed/sonic-OS-p4gw201911-1.0.0/sonic-patch show', 'docker exec -i pmon supervisorctl status xcvrd']
# EXEC_COMMANDS = ['./sonic-OS-p4gw201911-1.0.0.patch rollback']
# check tasks
# EXEC_COMMANDS = ['P=$(docker exec -i pmon supervisorctl status xcvrd | awk \'{ print $4 }\'| cut -d , -f1); docker exec -i pmon ls -l /proc/$P/task/ | tail -n +2 | wc -l']
EXEC_COMMANDS = ['docker exec -i pmon ps -ef | grep xcvrd | fgrep -v grep', 'P=$(docker exec -i pmon supervisorctl status xcvrd | awk \'{ print $4 }\'| cut -d , -f1); docker exec -i pmon ls -l /proc/$P/task/ | tail -n +2 | wc -l']


def obtain_remote_devices(filepath: str) -> List[str]:
    '''
    only obtain ipv4 address list
    skip '#' start lines
    '''
    device_ip_list: List[str] = []

    with open(filepath, 'r') as f:
        for line in f.readlines():
            if line.startswith("#"):
                continue
            arr = line.strip().split(',', 2)
            if len(arr) < 1 or '.' not in arr[0]:
                continue
            device_ip_list.append(arr[0])

    return device_ip_list


def run_remote_cmd(output_f, ip, user, pwd: str, commands: List[str]):
    ssh = paramiko.SSHClient()
    # auto add key to local KnownHosts
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(ip, username=user, password=pwd)

    # exec remote commands
    for command in commands:
        output_f.write("## exec: %s\n" % command)
        stdin, stdout, stderr = ssh.exec_command(command)
        str_stderr = stderr.read().decode()
        str_stdout = stdout.read().decode()
        if len(str_stderr) > 0:
            output_f.write("stderr:\n```shell\n%s\n```\n" % str_stderr.strip())
        if len(str_stdout) > 0:
            output_f.write("stdout:\n```shell\n%s\n```\n" % str_stdout.strip())

    ssh.close()


def get_output_dir(output_dir_name: str = 'output') -> str:
    script_dir = os.path.dirname(os.path.abspath(__file__))
    output_dir_abspath = script_dir + '/' + output_dir_name
    if not os.path.isdir(output_dir_abspath):
        os.makedirs(output_dir_abspath)
    return output_dir_abspath


def gen_output_log_file_abspath(device_list_file: str) -> str:
    str_now_time = datetime.now().strftime('%Y_%m_%d__%H_%M_%S')
    device_list_file_name = device_list_file.split('/')[-1]
    output_dir_abspath = get_output_dir()
    return output_dir_abspath + '/output_of_' + device_list_file_name + '_' + str_now_time + '.md'


def multiple_login_device_and_exec_cmds(device_list_file: str, commands: List[str]):
    output_file_abspath = gen_output_log_file_abspath(device_list_file)
    output_f = open(output_file_abspath, 'w')
    remote_device_list = obtain_remote_devices(device_list_file)

    for remote_device_ip in remote_device_list:
        print("# Login %s and run commands ..." % remote_device_ip)
        output_f.write("\n# %s\n" % remote_device_ip)
        run_remote_cmd(output_f, remote_device_ip, DEFAULT_USER, DEFAULT_PWD, commands)

    output_f.close()


def main():
    multiple_login_device_and_exec_cmds(DEVICE_LIST_FILE, EXEC_COMMANDS)
    print('Done.')


if __name__ == '__main__':
    main()
