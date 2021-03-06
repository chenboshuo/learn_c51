/**
 * 扫描所有按键，检测是否按下
 * 参考
 * ./reference/8_5_scan_all_keys.c
 */
#include "lib/alias.h"
#include "lib/data_tube.h"
#include "lib/interrupt.h"
#include "lib/key.h"
#include "lib/light.h"  // debug
#include "lib/system_header.h"

#define ADD_DOT_MASK 0x7F  /// 给行号增加小数点

static int just_pressed_line = -1, just_pressed_col = -1;

void main() {
  // static int date_tube_code = DIGITS_LED[0];  // 默认关闭
  static unsigned int line_id, col_id;

  // 计时一秒
  enable_timer_t0_with_interrupt();
  TIME_1MS();

  while (TRUE) {
    ;
  }
}

void flash_and_update() interrupt T0_OVERFLOW {
  unsigned char col_id;
  static unsigned char line_id = 0;
  static int data_tube_id = 0;

  // 更新计数器初值
  TIME_1MS();

  // 将一行按键移动到缓冲区
  for (col_id = 0; col_id < KEY_COL_SIZE; ++col_id) {
    update_key_buffer(line_id, col_id);  // 将按键状态移动到缓冲区
    update_key_status(line_id, col_id);  // 更新按键状态
  }

  // 刷新数码管
  if (data_tube_id == 1) {
    open_data_tube(1, DIGITS_LED[just_pressed_line + 1] & ADD_DOT_MASK);
  } else {
    open_data_tube(0, DIGITS_LED[just_pressed_col + 1]);
  }
  data_tube_id = 1 - data_tube_id;
  // open_lights(key_buffer[0][1] | 0xF0);

  for (col_id = 0; col_id < KEY_COL_SIZE; ++col_id) {
    if (is_just_pressed(line_id, col_id)) {
      // open_data_tube(0, DIGITS_LED[line_id * 4 + col_id]);
      // date_tube_code = DIGITS_LED[line_id * 4 + col_id];
      // open_data_tube(1, line_id);
      // open_data_tube(1, col_id);
      // date_tube_code = DIGITS_LED[0];
      just_pressed_line = line_id;
      just_pressed_col = col_id;
    }
  }

  // 更新linster
  ++line_id;  // 下一次刷新下一行
  line_id &= 0x03;
  set_listener_of_line(line_id);
}
