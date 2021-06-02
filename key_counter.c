/**
 * 测试按键
 * 记录按下按键的次数
 */
#include "lib/alias.h"
#include "lib/data_tube.h"
#include "lib/key.h"
#include "lib/light.h"
#include "lib/system_header.h"

void main() {
  unsigned int key_counter = 0;
  set_listener_of_line(1);
  while (TRUE) {
    open_data_tube(0, DIGITS_LED[key_counter]);  // 展示按键按下的次数
    key_counter += is_pressed(4, KEY_EVENT);     // 按下计数
    key_counter %= 9;                            // 只使用以为
    // open_lights(KEY_EVENT);
  }
}
