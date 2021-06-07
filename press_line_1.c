/**
 * 测试按键
 * 按下第一行按钮，
 * 检测是否读取到
 * 读取结果用LED灯显示
 */
#include "lib/alias.h"
#include "lib/key.h"
#include "lib/light.h"
#include "lib/system_header.h"

void main() {
  set_listener_of_line(0);
  while (TRUE) {
    open_lights(get_key_code());

    // 右起第三盏灯亮，表明在检测第一行有无按键按下
    // open_lights(KEY_EVENT);
  }
}
