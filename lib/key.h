/** @file
 * @defgroup  与按键有关的定义和函数
 * @{
 */

#ifndef KEY_H
#define KEY_H

#include "system_header.h"

#define KEY_EVENT P2  /// P2 用于处理键盘事件
#define PRESSED 0     /// 表示按键被按下

/**
 * 设置要检测的行
 * @param line_id 行号
 */
void set_listener_of_line(int line_id) {
  KEY_EVENT = ~(1 << (4 - line_id));  // 低四位用来设置行线的初值
}

/**
 * 获得按键的点击的键码，低四位表明行数，这个函数将它们屏蔽
 * 需要提前调用 set_listener
 * @param  line_id 要检测的行
 * @return         (a4 a3 a2 a1 1 1 1 1) ai=0 表示 line_id行的第i个键按下
 */
unsigned int get_key_code() {
  // 返回键码
  return ((KEY_EVENT & 0xF0)  // 保留高四位
          | 0x0F);            // 低四位补0
}

/**
 * 检测某一个按键是否按下(需要提前调用set_listener_of_line)
 * @param  col_id 列号
 * @return        按键是否被按下
 */
unsigned int is_pressed(int col_id, int state) {
  unsigned int mask = 1 << (3 + col_id);
  unsigned int old_state = state;
  if ((KEY_EVENT & mask) != (old_state & mask)) {
    unsigned int is_key_pressed = (KEY_EVENT & mask) == PRESSED;
    old_state = KEY_EVENT;
    return is_key_pressed;
  }
  return FALSE;
}

///@}

#endif
