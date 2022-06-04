#!/usr/bin/python
# -*- coding: utf-8 -*-

import os, sys
# import pexpect
import datetime
import time
import threading
from itertools import islice

g_count = 0
lock = threading.Lock() #申请一把锁

DEF_LIST_FILE = './dev_info.csv'
DELIMITER = ','                             # the delimiter of deviceList.txt
MAX_TASK_NUM = 40

def do_task(index_start, index_end, device_list):
    global g_count
    for i in range(index_start, index_end + 1):
        lock.acquire()
        g_count = g_count + 1
        lock.release()
        print("dev_ip: '%s'"%device_list[i][1])


def loop_login_and_execute(dev_list_file):
    start_time = time.time()
    global g_count
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
    print('size of device list is: %d', total_devices)

    # 任务量拆分
    remain_devices = 0

    if total_devices < MAX_TASK_NUM:
        task_num = total_devices
        a_task_devices = 1
    elif (total_devices % MAX_TASK_NUM) == 0:
        task_num = MAX_TASK_NUM
        a_task_devices = total_devices // MAX_TASK_NUM
    elif (total_devices % (MAX_TASK_NUM - 1)) == 0:
        task_num = MAX_TASK_NUM - 1
        a_task_devices = total_devices // (MAX_TASK_NUM - 1)
    else:
        task_num = MAX_TASK_NUM
        a_task_devices = total_devices // (MAX_TASK_NUM - 1)
        remain_devices = total_devices % (MAX_TASK_NUM - 1)

    # Loopping login device and executing commands
    # 并行执行
    for i in range(task_num):
        start = i * a_task_devices
        end = (i + 1) * a_task_devices - 1
        if (i == task_num - 1):
            end = total_devices - 1

        # Thread instantiation
        t = threading.Thread(target=do_task, args=(start, end, device_list))
        t.setName('TASK_%02d'%(i))
        threads.append(t)
        t.start()

    # waiting for threads end
    for t in threads:
        t.join()

    print('execute finished! (%d / %d)'%(g_count, total_devices))
    end_time = time.time()
    print('Runtime: %d s'%(end_time - start_time))



def main():
    # Parameter acquisition
    dev_list_file = (sys.argv[1] if (len(sys.argv) > 1 and len(sys.argv[1]) > 0) else DEF_LIST_FILE)

    # Batch processing
    loop_login_and_execute(dev_list_file)
    return 0


if __name__ == '__main__':
    main()
