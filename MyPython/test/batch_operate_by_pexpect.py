#!/usr/bin/python2
# -*- coding: utf-8 -*-

"""
The function of this module is batch automatic operating

Describe:
You just need to pay attention to the globally defined constants and the execution content of do_task()

Dependency package:
- pexpect   you can install this package by pip ( pip install pexpect -i https://pypi.tuna.tsinghua.edu.cn/simple )

Example usage:
-  ./batch_operate.py  ./dev_info.csv  ./batch_operate.log  machine_room_name(choose)  machine_room_ip(choose)
-  ./batch_operate.py
"""

import os, sys
import time
import logging
import pexpect
import datetime
import threading
import traceback
from itertools import islice

###########################  User defined start  ###########################
MAX_TASK_NUM = 16
PRINT_ON_SCREEN = True # True
LOG_EXPECT_DEBUG = True # False
IS_FIRST_LOGIN_CLI = True # True
DEF_LIST_FILE = './dev_info.csv'
DEF_LOG_FILE = './batch_operate.log'
DEF_USR_NAME = 'admin'
DEF_USR_PWD = 'xxx'
DEF_MR_NAME = 'ABC'
DEF_MR_IP = ''
DEF_MR_DIR = '~/batch_operate/'
###########################  User defined end  ###########################


#########  Don't change the fields below unless you know what it means  #########
# Global fields
g_mr_name = ''
g_mr_ip = ''
g_hostname_shell_match = ''
g_cmd_cli_2_shell = 'start shell bash'
g_fail_index_list = []
lock = threading.Lock() # apply for a lock
# Script-defined constants
DELIMITER = ','                             # the delimiter of deviceList.txt
TIME_FORMAT = '%Y-%m-%d.%H:%M:%S'           # the format of log time
MAX_WAIT_SEC = 15                           # the max waiting time of executing
MAX_RETRY_TIMES = 7
MAX_TWICE_EXEC = 2
MAX_TFTP_WAIT_SEC = 120
SUCCESS_CODE = 0
FAILED_CODE = -1
TIMEOUT_CODE = -2
REFRESH_SSH_STR = 'Host key verification failed'
REFRESHED_SSH_STR = 'Original contents retained'
SH_SCRIPT_FINISH_STR = 'extract_error_log.sh finished'
TFTP_UPLOAD_SUCCESS_STR = 'Successfully uploaded'
TFTP_UPLOAD_FAILED_STR = 'Failed to upload'
TFTP_TIMEOUT_STR = 'Transfer timed out'
YES_OR_NO_STR = 'yes/no'
PWD_INPUT_STR = '[P|p]assword:'
HOSTNAME_MATCH_STR = '[A-Z0-9\-]{20,}(\.Int){0,1}'
LOGIN_MATCH_STR = HOSTNAME_MATCH_STR + ' login:'
HOSTNAME_CLI_MATCH_STR = HOSTNAME_MATCH_STR + '>'


"""
Do the task which need to be executed on every device

Param:
dev_hdl: the Handle of pexpect of target device, through which you can execute task command
dev_ip: device ip

Return:
0   success
-1  failed
"""
def do_task(dev_hdl, dev_ip):
    global g_mr_name
    global g_mr_ip
    global g_hostname_shell_match
    global g_cmd_cli_2_shell
    last_dot_pos = dev_ip.rfind('.')
    dev_ip_seg = dev_ip[0:last_dot_pos]

    # Step0. Change to shell bash
    ret0 = send_and_run_a_cmd(dev_hdl, HOSTNAME_CLI_MATCH_STR, g_cmd_cli_2_shell)

    # ========================  Step1. Pull extract_error_log.sh  ==================================== #
    # 拼接 tftp 命令
    tftp_pull_cmd = 'tftp ' + (dev_ip_seg + '.5' if g_mr_ip == '' else g_mr_ip) + ' -c get extract_error_log.sh'
    send_and_run_a_cmd(dev_hdl, g_hostname_shell_match, tftp_pull_cmd)
    ret1 = -1
    try_times = 0
    while try_times < MAX_TWICE_EXEC:
        try_times = try_times + 1
        try:
            ret1 = dev_hdl.expect([TFTP_TIMEOUT_STR, g_hostname_shell_match, pexpect.EOF, pexpect.TIMEOUT], timeout = MAX_TFTP_WAIT_SEC)
            if ret1 == 0:
                logging.warn("Try tftp pulling extract_error_log.sh... failed(%s/%s), %s."%(try_times, str(MAX_TWICE_EXEC), TFTP_TIMEOUT_STR))
                # 重新发送 tftp 拉取命令
                send_and_run_a_cmd(dev_hdl, g_hostname_shell_match, tftp_pull_cmd)
                continue
            elif ret1 == 1:
                # sftp pull script success
                ret1 = SUCCESS_CODE
                break
        except pexpect.ExceptionPexpect:
                logging.error("Try tftp pulling extract_error_log.sh... failed(%s/%s), script waitting timeout."%(try_times, str(MAX_TWICE_EXEC)))

    if try_times >= MAX_TWICE_EXEC:
        print_and_log("Try tftp pulling extract_error_log.sh... failed. timeout.")
        return FAILED_CODE
    dev_hdl.sendline("\n")

    # ========================  Step2. Extracting error log  ==================================== #
    exec_script_cmd = 'sh ./extract_error_log.sh ' + g_mr_name + ('' if g_mr_ip == '' else ' ' + g_mr_ip)
    send_and_run_a_cmd(dev_hdl, g_hostname_shell_match, exec_script_cmd)
    # 等待捞日志脚本执行完成，单次最大等待时间 5 分钟，最多等待两个周期
    ret2 = -1
    b_is_tar_upload_success = False
    b_sh_script_finish = False
    check_unfinished_times = 0
    while check_unfinished_times < MAX_TWICE_EXEC:
        check_unfinished_times = check_unfinished_times + 1
        try:
            ret2 = dev_hdl.expect([TFTP_UPLOAD_SUCCESS_STR, TFTP_UPLOAD_FAILED_STR, SH_SCRIPT_FINISH_STR, pexpect.EOF, pexpect.TIMEOUT], timeout = 300)
            if ret2 == 0:
                b_is_tar_upload_success = True
                b_sh_script_finish = True
                # execute script success
                break
            elif ret2 == 1:
                b_is_tar_upload_success = False
                b_sh_script_finish = True
                break
            elif ret2 == 2:
                b_sh_script_finish = True
        except pexpect.ExceptionPexpect:
            logging.debug("Checking script executing unfinished(%s/%s)."%(check_unfinished_times, str(MAX_TWICE_EXEC)))
        

    if check_unfinished_times >= MAX_TWICE_EXEC and not b_sh_script_finish:
        # 若超时，则发送 ctrl + c 中止脚本
        print_and_log("Waiting for executing script finish more than 10 mins, kill script process.")
        dev_hdl.sendcontrol('c')
        return FAILED_CODE
    elif not b_is_tar_upload_success:
        # 提取异常日志成功，但上传 压缩文档失败
        print_and_log("successfully extract err log, but uploading tar.gz file failed!")
        return FAILED_CODE
    dev_hdl.sendline("\n")

    # ========================  Step3. Delete extract_error_log.sh  ==================================== #
    ret3 = send_and_run_a_cmd(dev_hdl, g_hostname_shell_match, 'rm -rf extract_error_log.sh')

    # ========================  Step4. Exit shell bash  ==================================== #
    ret4 = send_and_run_a_cmd(dev_hdl, g_hostname_shell_match, "exit")

    ret = (ret1 | ret2 | ret3 | ret4)
    if (ret == SUCCESS_CODE):
        return SUCCESS_CODE
    return FAILED_CODE


"""
Waiting for a echo str, then send a command str to target device to execute

Param:
dev_hdl:        the Handle of pexpect of target device, through which you can execute task command
expect_pattern: the expect echo pattern
cmd_str:        the command str, will use "" instead if not input

Return:
-1              mismatch or some except occur when wating for expect_pattern
0               matched, and has sent the cmd str
1 ~ n           matched the index of the pattern list
"""
def expect_and_send_str(dev_hdl, expect_pattern, cmd_str = "", wait_time = MAX_WAIT_SEC):
    try:
        index = dev_hdl.expect(expect_pattern, timeout = wait_time)
        if (index == 0 and len(cmd_str) > 0):
            dev_hdl.sendline(cmd_str)
    except pexpect.EOF:
        logging.error("Some pexpect.EOF except occur when wating for expect_pattern: %s"%expect_pattern)
        index = -1
    except pexpect.TIMEOUT:
        if wait_time != 0:
            logging.error("Some pexpect.TIMEOUT except occur when wating for expect_pattern: %s"%expect_pattern)
        index = -1
    except pexpect.ExceptionPexpect:
        logging.error("An pexpect.ExceptionPexpect occur when wating for expect_pattern: %s"%expect_pattern)
        index = -1
    finally:
        return index


"""
Send a cmd str, and it will be run in the target device

Param:
dev_hdl:    the Handle of pexpect of target device, through which you can execute task command
match_str:  expect match string
cmd_str:    the command str

Return:
0   success
1   error, some pexpect except occur
-1  error, some except occur when executed cmd
"""
def send_and_run_a_cmd(dev_hdl, match_str, cmd_str, wait_time = MAX_WAIT_SEC):
    try:
        # Send the cmd str
        ret = expect_and_send_str(dev_hdl, match_str, cmd_str, wait_time)

        # pexpect package bug fix: If the echo is not received in advance, it will cause the next need sending command to be triggered early
        expect_and_send_str(dev_hdl, match_str, "", 0)

        return (SUCCESS_CODE if (ret == 0) else 1)
    except Exception as e:
        logging.error("Warning: some except occur when target device executed cmd: %s, %s"%(cmd_str, str(traceback.print_exc())))
        return FAILED_CODE


"""
Both print a str to terminal and write the str into log file
"""
def print_and_log(out_str):
    # logging to log file
    logging.info(out_str)
    # whether print to screen
    if PRINT_ON_SCREEN:
        now_time_str = datetime.datetime.now().strftime(TIME_FORMAT)
        out_str_with_time = now_time_str + "  " + out_str
        print(out_str_with_time)


"""
Login a single device and perform tasks

Param:
dev_name:       the name of device
dev_ip:         the ip of device
log_file_fp:    the file point of the log file

Return:
0   success
-1  failed
"""
def login_a_device_and_exec(dev_name, dev_ip, log_file_fp):
    ret = 0
    global g_hostname_shell_match
    global g_cmd_cli_2_shell
    login_cmd = "telnet " + dev_ip
    device_info = dev_name + "(" + dev_ip + ")"
    hostname_match = (HOSTNAME_CLI_MATCH_STR if IS_FIRST_LOGIN_CLI else g_hostname_shell_match)
    sys.stdout.flush()

    try:
        # Login target device
        dev_hdl = pexpect.spawn(login_cmd, timeout = MAX_WAIT_SEC)

        # [debug log]: write the echo message to log file
        if LOG_EXPECT_DEBUG:
            dev_hdl.logfile = log_file_fp

        # Waiting for "login:", and send user name
        failed_login_times = 0
        while failed_login_times < MAX_RETRY_TIMES:
            try:
                ret = dev_hdl.expect([REFRESH_SSH_STR, REFRESHED_SSH_STR, YES_OR_NO_STR, LOGIN_MATCH_STR, PWD_INPUT_STR, hostname_match, pexpect.EOF, pexpect.TIMEOUT], timeout = MAX_WAIT_SEC)
                if ret == 0:
                    dev_hdl.sendline("ssh-keygen -f ~/.ssh/known_hosts -R '%s'"%dev_ip)
                elif ret == 1:
                    dev_hdl.sendline("telnet %s"%dev_ip)
                elif ret == 2:
                    dev_hdl.sendline("yes")
                elif ret == 3:
                    dev_hdl.sendline(DEF_USR_NAME)
                elif ret == 4:
                    dev_hdl.sendline(DEF_USR_PWD)
                elif ret == 5:
                    # successfully login
                    break
                else:
                    logging.error("Try logining %s ... failed(%s/%s), unknown expect string."%(device_info, 1 + failed_login_times, str(MAX_RETRY_TIMES)))
            except pexpect.ExceptionPexpect:
                logging.error("Try logining %s ... failed(%s/%s), a pexpect exception occur."%(device_info, 1 + failed_login_times, str(MAX_RETRY_TIMES)))

            failed_login_times = failed_login_times + 1

        if failed_login_times >= MAX_RETRY_TIMES:
            print_and_log("Try logining %s ... failed."%device_info)
            return FAILED_CODE

        print_and_log("Try logining %s ... success."%device_info)
        dev_hdl.sendline("\n")

        # 检查 SONIC 版本
        send_and_run_a_cmd(dev_hdl, HOSTNAME_CLI_MATCH_STR, "show version | grep SONiC")

        ret = dev_hdl.expect(['SONiC\.0\.9[\.0-9]{1,}', 'SONiC\.1[\.0-9]{1,}', pexpect.EOF, pexpect.TIMEOUT], timeout = MAX_WAIT_SEC * 10)
        # 99 版本的SONIC，切换到shell命令不同
        if ret == 0:
            g_hostname_shell_match = '\$'
            g_cmd_cli_2_shell = 'start-shell shell'
        elif (ret == 2 or ret == 3):
            # 若超时，则发送 ctrl + c 中止 show version
            dev_hdl.sendcontrol('c')
            g_hostname_shell_match = '\$'
            g_cmd_cli_2_shell = 'start-shell shell'
        else:
            g_hostname_shell_match = DEF_USR_NAME + '@' + HOSTNAME_MATCH_STR
            g_cmd_cli_2_shell = 'start shell bash'

        dev_hdl.sendline("\n")

        # ************ Do task start ************
        ret = do_task(dev_hdl, dev_ip)
        # ************  Do task end  ************

        print_and_log("Executing task on %s ... %s.\n"%(device_info, ('success' if (ret == SUCCESS_CODE) else 'failed')))

        # Logout target device
        dev_hdl.sendline("\n")
        expect_and_send_str(dev_hdl, hostname_match, "exit")

        return ret

    except:
        logging.error("Except: an unknown exception occurred in logining %s. Except msg: %s\n"%(device_info, str(traceback.print_exc())))
    finally:
        if dev_hdl != None:
            dev_hdl.close()


"""
Operate multiple devices

Param:
index_start:    start index of device list
index_end:      end index of device list
device_list:    list of all devices
log_file_fp:    the file point of the log file
"""
def operate_mul_devices(index_start, index_end, device_list, log_file_fp):
    global g_fail_index_list
    max_available_index = len(device_list) - 1

    if index_start > max_available_index:
        return
    elif index_end > max_available_index:
        index_end = max_available_index

    for i in range(index_start, index_end + 1):
        [dev_name, dev_ip] = device_list[i]
        # *************** Login and operate start ***************
        ret = login_a_device_and_exec(dev_name, dev_ip, log_file_fp)
        if ret == FAILED_CODE:
            lock.acquire()
            g_fail_index_list.append(i)
            lock.release()
        # *************** Login and operate start ***************


"""
Login to the device and perform tasks in a poll

Param:
dev_list_file:  the file which list the devices to be repaired
log_file_fp:    the file point of the log file
"""
def parallel_run(dev_list_file, log_file_fp):
    start_time = time.time()
    print_and_log("==================== Parallel execute Startting ====================\n")
    device_list = []
    threads = []

    # Extra device name and ip from device file
    with open(dev_list_file, 'r+') as f:
        for dev_info_line in islice(f, 1, None):
            res_list = dev_info_line.split(DELIMITER, 2)
            if len(res_list) < 2:
                continue
            device_list.append(res_list[:2])

    total_devices = len(device_list)

    # Task split and Parallel execution
    print_and_log('The num of devices is: %s'%str(total_devices))

    if total_devices < MAX_TASK_NUM:
        task_num = total_devices
        a_task_devices = 1
    elif (total_devices % MAX_TASK_NUM) == 0:
        task_num = MAX_TASK_NUM
        a_task_devices = total_devices // MAX_TASK_NUM
    else:
        a_task_devices = total_devices // MAX_TASK_NUM + 1
        task_num = total_devices // a_task_devices + 1

    print_and_log('The num of thread is: %s'%str(task_num))

    if task_num == 1:
        operate_mul_devices(0, total_devices - 1, device_list, log_file_fp)
    else:
        for i in range(task_num):
            start = i * a_task_devices
            end = (i + 1) * a_task_devices - 1

            # Thread instantiation
            t = threading.Thread(target=operate_mul_devices, args=(start, end, device_list, log_file_fp))
            t.setName('TASK_%02d'%(i))
            threads.append(t)
            t.start()

        # waiting for threads end
        for t in threads:
            t.join()

    failed_op_num = len(g_fail_index_list)
    end_time = time.time()
    print_and_log("====================  Parallel execute finished!  ====================\n")
    print_and_log("Success operation devices: ( %d / %d ), Runtime: ( %s s )"%(total_devices - failed_op_num, total_devices, str(end_time - start_time)))
    if failed_op_num > 0:
        print_and_log("====================  A total of ( %d ) device operations failed:  ===================="%failed_op_num)
        for i in g_fail_index_list:
            print_and_log("%s,%s"%(device_list[i][0], device_list[i][1]))
    print("\n")


"""
main program

Param:
dev_list_file:  the file which list the devices to be repaired
dev_log_file:   the file which reward the logs of devices
g_mr_name:       the name of the machine room
g_mr_ip:         the ip of the machine room
"""
def main():
    global g_hostname_shell_match
    global g_mr_name
    global g_mr_ip
    log_file_fp = None

    # Parameter acquisition
    dev_list_file = (sys.argv[1] if (len(sys.argv) > 1 and len(sys.argv[1]) > 0) else DEF_LIST_FILE)
    dev_log_file = (sys.argv[2] if (len(sys.argv) > 2 and len(sys.argv[2]) > 0) else DEF_LOG_FILE)
    g_mr_name = (sys.argv[3] if (len(sys.argv) > 3 and len(sys.argv[3]) > 0) else DEF_MR_NAME)
    g_mr_ip = (sys.argv[4] if (len(sys.argv) > 4 and len(sys.argv[4]) > 0) else DEF_MR_IP)
    g_hostname_shell_match = DEF_USR_NAME + '@' + HOSTNAME_MATCH_STR

    # logging setting
    logging.basicConfig(filename= dev_log_file, filemode='a', format= '%(asctime)s.%(msecs)03d %(levelname)-8s : - %(message)s', datefmt= TIME_FORMAT, level=logging.INFO)

    # [debug log]: write the echo message to log file
    if LOG_EXPECT_DEBUG:
        log_file_fp = open(dev_log_file, "a+")

    print_and_log("Starting batch_operate.py with input params:\n  - dev_list_file: '%s'\n  - dev_log_file: '%s'\n  - mr_name: '%s'\n  - mr_ip: '%s'\n  - user name: '%s'\n\n"%(dev_list_file, dev_log_file, g_mr_name, g_mr_ip,  DEF_USR_NAME))

    # Batch processing
    parallel_run(dev_list_file, log_file_fp)

    if log_file_fp != None:
        log_file_fp.close()

    return 0


if __name__ == '__main__':
    main()
