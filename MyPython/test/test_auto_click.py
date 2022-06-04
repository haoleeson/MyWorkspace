#!/usr/bin/python3
# -*- coding: utf-8 -*-

from pymouse import PyMouse   #调用Pymouse模块
import time   #调用时间模块(考略到网站点击延时)

# # 初始化鼠标对象
# m = PyMouse()
# 获取当前坐标的位置
# m.position()
# # 获取当前屏幕大小
# m.screen_size()
# # 鼠标滚动（垂直滚动10单位）
# m.scroll(10, 0)
# # 鼠标拖拽(从当前位置拖拽到目标位置)
# m.drag(500, 300)

def print_x_y_position(repeat_times = 5):
    # 初始化鼠标对象
    m = PyMouse()
    for i in range(repeat_times): # 循环n次
        print('Get mouse position...')
        a = m.position()   #获取当前坐标的位置
        print(a)   #显示位置
        time.sleep(5)  #延时 5 秒

def loop_click(x, y, repeat_times = 5):
    # 初始化鼠标对象
    m = PyMouse()
    for i in range(repeat_times): # 循环n次
        m.move(x, y) # 鼠标移动至坐标(x, y)
        # m.click(x, y, button, n) -- 点击，想x,y坐标，button：-1表示左键，-2表示右键，n：默认1次，2双击
        m.click(x, y) # 鼠标点击坐标(x, y)


def main():
    # 检查鼠标位置
    print_x_y_position(3)

    # 重复点击
    # loop_click(800, 600, 5)
    return 0


if __name__ == '__main__':
    main()
