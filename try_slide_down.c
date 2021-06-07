/** @file
 * 根据参考代码改变文字方向(由下到上动态显示)
 *
 * 参考：7_2_dynamic_show_i_love_you
 *
 * 书本内容：第7章 LED点阵显示纵向移动的动画 第7章7.5.1节
 */
#include "mylib.h"

#define ARRAY_SIZE 32  //!< 图片分为若干个单元，32为最后一个单元
#define SILDE_PERIOD 250  //!< 滑动周期250ms

/**
 * 图片的字模表
 */
unsigned char code image[ARRAY_SIZE] = {
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0x99,  // .@@..@@.
    0x99,  // .@@..@@.
    0x99,  // .@@..@@.
    0x99,  // .@@..@@.
    0x99,  // .@@..@@.
    0x81,  // .@@@@@@.
    0xC3,  // ..@@@@..
    0xFF,  // ........
    0x99,  // .@@..@@.
    0x00,  // @@@@@@@@
    0x00,  // @@@@@@@@
    0x00,  // @@@@@@@@
    0x81,  // .@@@@@@.
    0xC3,  // ..@@@@..
    0xE7,  // ...@@...
    0xFF,  // ........
    0xC3,  // ..@@@@..
    0xE7,  // ...@@...
    0xE7,  // ...@@...
    0xE7,  // ...@@...
    0xE7,  // ...@@...
    0xE7,  // ...@@...
    0xC3,  // ..@@@@..
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF,  // ........
    0xFF   // ........
};
void main() {
  enable_timer_t0_with_interrupt();
  TIME_1MS();
  while (TRUE) {
    ;
  }
}

/**
 * T0溢出中断服务函数，
 * T0溢出一次刷新一次，
 * 每250ms 更新一次显示图像
 */
void flash_and_slide() interrupt T0_OVERFLOW {
  static unsigned char row_id = 0;    // 每次中断刷新一行
  static unsigned char ms_count = 0;  // 记录经过的毫秒数

  // 图片单元，由下往上，首先是最后一个单元
  static unsigned char image_unit = 32;

  ++ms_count;  // 经过1ms

  // 重新加载初值
  TIME_1MS();

  // 刷新图像
  show_in_array(row_id, image[image_unit + row_id]);
  ++row_id;
  row_id %= ROW_SIZE;

  // 没 250 ms 刷新一次图像，显示上一单元
  if (ms_count == SILDE_PERIOD) {
    ms_count = 0;
    --image_unit;
    if (image_unit == 0) {
      image_unit = ARRAY_SIZE;
    }
  }
}
