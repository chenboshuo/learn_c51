/** @file
 * 制作字模，在点阵中显示数字
 *
 * 在程序中进行一秒钟倒计时
 */
#include "mylib.h"

#define ARRAY_SIZE 72  //!< 图片分为若干个单元，32为最后一个单元
#define SILDE_PERIOD 1000  //!< 滑动周期100ms

/**
 * 图片的字模表
 */
unsigned char code image[ARRAY_SIZE] = {
    0xff,  // ........
    0x81,  // .######.
    0xbd,  // .#....#.
    0xbd,  // .#....#.
    0x81,  // .######.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0x81,  // .######.
    0xff,  // ........
    0x81,  // .######.
    0xbd,  // .#....#.
    0xbd,  // .#....#.
    0x81,  // .######.
    0xbd,  // .#....#.
    0xbd,  // .#....#.
    0x81,  // .######.
    0xff,  // ........
    0x81,  // .######.
    0xdf,  // .....#..
    0xef,  // ....#...
    0xf7,  // ...#....
    0xfb,  // ..#.....
    0xfd,  // .#......
    0xff,  // ........
    0xff,  // ........
    0x81,  // .######.
    0xfd,  // .#......
    0xfd,  // .#......
    0x81,  // .######.
    0xbd,  // .#....#.
    0xbd,  // .#....#.
    0x81,  // .######.
    0xff,  // ........
    0x81,  // .######.
    0xfd,  // .#......
    0xfd,  // .#......
    0x81,  // .######.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0x81,  // .######.
    0xff,  // ........
    0xbd,  // .#....#.
    0xbd,  // .#....#.
    0xbd,  // .#....#.
    0x81,  // .######.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0xff,  // ........
    0x81,  // .######.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0x81,  // .######.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0x81,  // .######.
    0xff,  // ........
    0x81,  // .######.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0x81,  // .######.
    0xfd,  // .#......
    0xfd,  // .#......
    0x81,  // .######.
    0xff,  // ........
    0xbf,  // ......#.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0xbf,  // ......#.
    0xbf   // ......#.
};
void main() {
  enable_timer_t0_with_interrupt();
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
  static unsigned char row_id = 0;  // 每次中断刷新一行
  static int ms_count = 0;          // 记录经过的毫秒数

  // 图片单元，由下往上，首先是最后一个单元
  static unsigned char image_unit = 0;

  ++ms_count;  // 经过1ms

  // 重新加载初值
  TIME_1MS();

  // 刷新图像
  show_in_array(row_id, image[image_unit + row_id]);
  ++row_id;
  row_id %= ROW_SIZE;

  // 没 1000 ms 刷新一次图像，显示上一单元
  if (ms_count == SILDE_PERIOD) {
    ms_count = 0;
    image_unit += ROW_SIZE;
    if (image_unit == ARRAY_SIZE) {
      image_unit = 0;
    }
  }
}
