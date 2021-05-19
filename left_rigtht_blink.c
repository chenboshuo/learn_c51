/** @file
 * 流水灯左右移动并闪烁
 * 现象：
 * 从右往左闪烁三次，到头之后返回
 */

#include "mylib.h"

#define LEFT_TO_RIGHT 1

void main() {
  unsigned int mask = 1;
  int direct = LEFT_TO_RIGHT;
  ADDRESS = ENABLE_LED_ARRAYS;  // set addr
  while (TRUE) {
    if ((mask & CLOSE_ALL) == 0) {  // mask 出范围，重新初始化
      // 根据指定方向初始化到最左边或最右边
      mask = (direct == LEFT_TO_RIGHT) ? 128 : 1;
      direct *= -1;  // 到边界改变方向
    }
    DATA = CLOSE_ALL & mask;
    DATA = ~DATA;  // mask 是在指定位置内的1(CLOSE),我们取反让指定位置打开
    blink(3);
    if (direct == LEFT_TO_RIGHT) {
      mask <<= 1;
    } else {
      mask >>= 1;
    }
  }
}
