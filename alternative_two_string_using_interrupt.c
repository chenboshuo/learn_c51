/**
 * 设置标志位，
 * 交替显示 hello! 和 123456
 * (中断方式实现)
 * 同时使用LED灯对5s进行计时
 */
#include <reg52.h>

#include "myheader.h"

#define FIVE_DOTS 0xe0  // 点亮最右边5个led灯

#define init_t0() \
  TH0 = 0xFC;     \
  TL0 = 0x67;  //重新加载初值，计时1ms

char string_chose = 0;    // 确定显示的字符串
int interrupt_count = 0;  // 中断计数，确定毫秒数
int tube_id = 0;
int led_bits = FIVE_DOTS;

// 显示 HELLO! 和 123456
unsigned char code characters[2][6] = {"!OLLEH", "654321"};

void main() {
  TMOD = 0x01;  // 设置T0为模式1
                // T0 = TIME_1_MS;             // 计时初值1ms
  init_t0();
  ALLOW_INTERRUPT = TRUE;     // 使能总中断
  ALLOW_T0_INTERRUPT = TRUE;  // 使能 T0 中断
  T0_STATUS = ENABLE;         // 启动 T0
  while (TRUE) {
    ;
  }
}

void alternative_and_flash() interrupt T0_OVERFLOW {
  ++interrupt_count;
  // T0 = 0xfc67;
  init_t0();

  // 终端 5000 次说明经过5s，改变标志位
  if (interrupt_count == 5000) {
    interrupt_count = 0;
    string_chose = 1 - string_chose;
    led_bits = 0xe0;
  } else if (interrupt_count % 1000 == 0) {
    // 中断1000 次说明经过1s，led 右移一位
    led_bits >>= 1;         // 每秒钟led灯右移
    led_bits |= FIVE_DOTS;  // 高位补1
  }

  // 中断一次刷新数码管一次
  show_char(tube_id, characters[string_chose][tube_id]);
  ++tube_id;
  tube_id %= 6;

  // 使用LED 灯计时
  DATA = CLOSE_ALL;  // 个人认为对LED消隐更明显
  ADDRESS = ENABLE_LED_ARRAYS;
  DATA = led_bits;
}
