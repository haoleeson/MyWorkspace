#!/usr/bin/python
# -*- coding: utf-8 -*-

import logging
# import datetime

RUN_LOG_FILE='/Users/admin/code/Python/test_logging.log'
TIME_FORMAT = '%Y-%m-%d %H:%M:%S'           # the format of log time

def create_list_log():
    # now_time_str = datetime.datetime.now().strftime(TIME_FORMAT)
    # tag_info_str = "\n[" + now_time_str + "] wrote log list:\n"
    # log_file_fp = open(RUN_LOG_FILE, "a")
    # log_file_fp.write(tag_info_str)
    # log_file_fp.close()
    logging.critical('test critical msg')
    logging.error('test error msg')
    logging.warning('test warning msg')
    logging.info('test info msg')
    logging.debug('test debug msg')


def main():
    logging.basicConfig(filename= '/Users/admin/code/Python/test_logging1.log',
        filemode='a', # w - 覆盖； ab - 追加；
        format= '%(asctime)s.%(msecs)03d %(levelname)-8s : - %(message)s',
        datefmt= TIME_FORMAT,
        level=logging.INFO) # 设定最低输出日志级别为：ERROR（低于此级别的日志不会输出到 log 文件）

    create_list_log()

    # 更改最低输出日志级别为：DEBUG
    logger = logging.getLogger()
    logger.setLevel(logging.ERROR)

    create_list_log()

    # 更改最低输出日志级别为：DEBUG
    logger = logging.getLogger('')
    logger.setLevel(logging.DEBUG)

    create_list_log()


if __name__ == "__main__":
    main()
