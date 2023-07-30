#!/usr/bin/python
# -*- coding: utf-8 -*-

# A simple loop click mouse left key script
# dependency: pyautogui
#   - python -m pip install -U pyautogui


import sys
import time
import pyautogui


# const value
DEFAULT_INTERVAL = 1.000
UNLIMITED_LOOP_TIMES = -1
DEFAULT_WAITING_MOVE_MOUSE_SECONDS = 5


# close fail safe to skip pyautogui bug
pyautogui.FAILSAFE = False


def get_mouse_position_seconds_later(waiting_seconds: int=DEFAULT_WAITING_MOVE_MOUSE_SECONDS) -> (int, int):
    x, y = 0, 0
    print("Please move your mouse pointer to target position, %d seconds latter will confirm...\n" % waiting_seconds)
    for i in range(waiting_seconds * 10):
        time.sleep(0.1)
        try:
            x, y = pyautogui.position()
            print('\r', "( %d, %d )    " % (x, y), end='')
        except KeyboardInterrupt as e:
            print('A KeyboardInterrupt exception occur, %s', str(e))
    print('')
    return (x, y)


def get_input_int_num(prompt: str, default_value: int) -> int:
    str_input = input(prompt)
    str_input = str_input.strip()
    if not str_input or str_input == "":
        num = default_value
    else:
        num = int(str_input)
    return num


def get_input_float_num(prompt: str, default_value: float) -> float:
    str_input = input(prompt)
    str_input = str_input.strip()
    if not str_input or str_input == "":
        num = default_value
    else:
        num = float(str_input)
    return num


def loop_click_mouse(position_x: int, position_y: int, loop_times: int=UNLIMITED_LOOP_TIMES, interval: float=DEFAULT_INTERVAL):
    i = 1
    while True:
        if loop_times != UNLIMITED_LOOP_TIMES and i > loop_times:
            break
        # param description:
        # - clicks:     single click or double click [default is 1]
        # - duration:   time cost to move mouse to target position [default is 0]
        pyautogui.click(position_x, position_y, clicks=1, duration=0)
        print('\r', "clicked ( %d, %d ) ......................... the %d / %d times      " % (position_x, position_y, i, loop_times), end='')
        time.sleep(interval)
        if i == sys.maxsize:
            i = 0
        i = i + 1
    print('Done')


def main():
    # get target click position
    x, y = get_mouse_position_seconds_later()
    print("    Your target position is: (%d, %d)\n" % (x, y))

    # get loop times
    loop_times = get_input_int_num('Please input the loop times(default is not limited): ', UNLIMITED_LOOP_TIMES)
    print("    Your target loop times is: %d\n" % loop_times)

    # get interval
    interval = get_input_float_num('Please input the interval(default is 1.000 second): ', DEFAULT_INTERVAL)
    print("    Your interval time is: %f second\n" % interval)

    # loop click
    loop_click_mouse(x, y, loop_times, interval)


if __name__ == '__main__':
    main()