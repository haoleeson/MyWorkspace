#!/usr/bin/python
# -*- coding: utf-8 -*-

import time
import pyautogui

# install pyautogui lib
# python -m pip install -U pyautogui


def get_cur_mouse_position() -> (int, int):
    x, y = pyautogui.position()
    return x, y


def click_position(x, y, duration=1, button='right'):
    pyautogui.click(x, y, duration)
    print("clicked %d, %d" % (x, y))


def auto_click_cur_position(max_loop_time, interval=1):
    x, y = pyautogui.position()

    for i in range(max_loop_time):
        print("clicked %d, %d the %d / %d times" % (x, y, i+1, max_loop_time))
        pyautogui.click(x, y, 1)
        time.sleep(interval)


def main():
    auto_click_cur_position(3, 1)


if __name__ == '__main__':
    main()