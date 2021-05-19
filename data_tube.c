/** @file
 * 在右上角数码管显示交替HELlo
 * 每个字符显示1s
 */
//

#include "mylib.h"

void main() {
  while (TRUE) {
    show_char(4, 'H');
    keep_one_second();
    show_char(3, 'E');
    keep_one_second();
    show_char(2, 'L');
    keep_one_second();
    show_char(1, 'l');
    keep_one_second();
    show_char(0, '0');
    keep_one_second();
  }
}
