#include <reg52.h>
#define OVERFLOW 1
#define NOT_OVERFLOW 0
#define DATA P0  // P0 寄存器一般传递数据，为了阅读方便，改名为 DATA
#define ADDRESS \
  P1  // P1 储存地址信息，低五位分别对应 ENLD,ADDR3,ADDR2,ADDR1,ADDR0
#define SLEEP_ROUND 30000  // 睡眠时间是 30000 个for循环
#define OPEN 0
#define CLOSE 1
#define ENABLE_LED_ARRAYS 14  // 01110
#define CLOSE_ALL 255
#define TRUE 1

// 数码管共阳极
// code 说明指定数组存在 flash ROM 中，
// 没有 code 会存到片内 RAM 中
unsigned char code DIGITS_LED[] = {
    //         dp g f e; d c b a
    0xC0,  // 0: 1 1 0 0; 0 0 0 0
    0xF9,  // 1: 1 1 1 1; 1 0 0 1
    0xA4,  // 2: 1 0 1 0; 1 1 0 0
    0xB0,  // 3: 1 0 1 1; 0 0 0 0
    0x99,  // 4: 1 0 0 1; 1 0 0 1
    0x92,  // 5: 1 0 0 1; 0 0 1 0
    0x82,  // 6: 1 0 0 0; 0 0 1 0
    0xF8,  // 7: 1 1 1 1; 1 0 0 0
    0x80,  // 8: 1 0 0 0; 0 0 0 0
    0x90,  // 9: 1 0 0 1; 0 0 0 0
    0x88,  // A: 1 0 0 0; 1 0 0 0
    0x83,  // B: 1 0 0 0; 0 0 1 1
    0xC6,  // C: 1 1 0 0; 0 1 1 0
    0xA1,  // D: 1 0 1 0; 0 0 0 1
    0x86,  // E: 1 0 0 0; 0 1 1 0
    0x8E   // F: 1 0 0 0; 1 1 1 0
};

/** 大约计时1s
 * 忽略访问内存时间
 * 采用T1定时 50ms
 * 然后循环 20次，计时大约1s
 */
void keep_one_second() {
  char count = 0;  // 记录T0中断次数
  TMOD = 0x10;  // 设置T0为模式1 TMOD 高四位控制T1 GATE=0 T/C = 0 (M1 M0) = 1
                // 工作方式 模式1

  T1 = 0x4c00;
  /*
   * TL1 = 0x00;
   * TH1 = 0xB8;  // 为T0赋初值0xB800, 根据主频计算计时20ms的初值
   * 以下是计时20ms 的初值，t20_two = 0xB800
   * t20 = 2^16 - t20_two
   * t50 = t20/2 * 5
   * t50_two = 2^16 - t50 = 19456
   * TH0 = 0xB8;  // 重新赋初值
   * TL0 = 0x00;
   */
  TR1 = 1;  // 启动T1

  while (count < 20) {
    if (TF1 == OVERFLOW) {  // T1溢出
      TF1 = NOT_OVERFLOW;   // T1溢出后，清零中断标志
      T1 = 0x4c00;          // 0x4c00

      ++count;  //计数值自加1
    }
  }
}
/** 使某一数码管显示某字符
 * @param digit_tube_id 管子的id 0-5 表示 LEDS0-LEDS5
 *                      也可以直接输入寄存器P1 的取值
 * @param c             显示的字符串
 */
void show_char(char digit_tube_id, char c) {
  ADDRESS = digit_tube_id | 0x08;  // 8 指 ADDR3 = 1
  switch (c) {                     // dp g f e; d c b a
    case 'H':
      DATA = 0x89;  //  1 0 0 0; 1 0 0 1
      break;
    case 'E':
      DATA = 0x86;  //  1 0 0 0; 0 1 1 0
      break;
    case 'L':
      DATA = 0xc7;  //  1 1 0 0; 0 1 1 1
      break;
    case 'l':  //  1 1 0 0; 1 1 1 1
      DATA = 0xcf;
      break;
    case 'O':
    case 'o':
      DATA = 0xC0;  //   1 1 0 0; 0 0 0 0
      break;
    default:
      DATA = DIGITS_LED[c - '0'];
      break;
  }
}

void sleep() {
  int i = SLEEP_ROUND;
  while (i--) {
    ;
  }
}

void blink(int t) {
  unsigned int pre, i;
  for (i = 0; i < t; ++i) {
    sleep();
    pre = DATA;  // backup
    DATA = CLOSE_ALL;
    sleep();
    DATA = pre;
  }
}
