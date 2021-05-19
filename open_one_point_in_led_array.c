/** @file
 * 点亮一个点阵的点,
 * 停顿片刻点亮一行
 * 现象: 第一行(0-indexed) 点亮一个led,
 * 很快点亮整个第一行
 * 循环显示
 */

#include "mylib.h"

void main() {
  while (TRUE) {
    show_in_array(1, 0xFE);  // 点亮第一行最左边的一个点
    sleep();
    DATA = CLOSE_ALL;
    show_in_array(1, 0);  // 点亮第一行
    sleep();
  }
}
