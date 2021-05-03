/**
 * 设置标志位，
 * 交替显示 hello! 和 123456
 * (中断方式实现)
 */
#include <reg52.h>

#include "myheader.h"
char string_chose = 0;
int interrupt_count = 0;
int tube_id = 0;
unsigned char code characters[2][6] = {"!OLLEH", "654321"};

void main() {
  TMOD = 0x01;  // 设置T0为模式1
                // T0 = TIME_1_MS;             // 计时初值1ms
  TH0 = 0xFC;   //重新加载初值
  TL0 = 0x67;

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
  TH0 = 0xfc;  //重新加载初值
  TL0 = 0x67;

  // 终端 5000 次说明经过5s，改变标志位
  if (interrupt_count == 5000) {
    interrupt_count = 0;
    string_chose = 1 - string_chose;
  }

  // 中断一次刷新数码管一次
  show_char(tube_id, characters[string_chose][tube_id]);

  ++tube_id;
  tube_id %= 6;
}
