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
  while (TRUE) {
    open_lights(get_key_code(1));
  }
}
