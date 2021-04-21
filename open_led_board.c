/**
 * 在开发版上点亮一盏灯
 */
#include <reg52.h>
#define SLEEP_TIME 30000
#define OPEN 0
#define CLOSE 1
#define ENABLE_LED_ARRAYS 14  // 01110
#define CLOSE_ALL 255

void sleep() {
  int i = SLEEP_TIME;
  while (i--) {
    ;
  }
}

void main() {
  P1 = ENABLE_LED_ARRAYS;  // set addr
  P0 = CLOSE_ALL;
  int mask = 1;
  while (1) {
    P0 = P0 & mask;
    sleep();
    mask <<= 1
  }
}
