/** @file
 * @defgroup  与按键有关的定义和函数
 * @{
 */

#ifndef KEY_H
#define KEY_H

#include "system_header.h"
#define KEY_EVENT P2  /// P2 用于处理键盘事件

/**
 * 获得按键的点击时间
 * @param  line_id 要检测的行
 * @return         (a4 a3 a2 a1 1 1 1 1) ai=0 表示 line_id行的第i个键按下
 */
unsigned int get_key_code(int line_id) {
  KEY_EVENT = (~(1 << (4 - line_id))) & 0xFF;
  return ((KEY_EVENT & 0xF0) | 0x0F);
}

///@}

#endif
