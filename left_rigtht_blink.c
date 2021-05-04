/**
 * 流水灯左右移动并闪烁
 * 现象：
 * 从右往左闪烁三次，到头之后返回
 */

#include "mylib.h"

void main() {
  unsigned int mask = 1;
  int direct = 1;
  P1 = ENABLE_LED_ARRAYS;  // set addr
  while (1) {
    if ((mask & CLOSE_ALL) == 0) {
      mask = (direct == 1) ? 128 : 1;
      direct *= -1;
    }
    P0 = CLOSE_ALL & mask;
    P0 = ~P0;
    blink(3);
    if (direct == 1) {
      mask <<= 1;
    } else {
      mask >>= 1;
    }
  }
}
