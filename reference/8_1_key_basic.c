/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：main.c
* 描  述：第8章 按键基本原理演示例程
* 版本号：v1.0.0
* 备  注：详情见第8章8.4.3节
*******************************************************************************
*/

#include <reg52.h>

sbit ADDR0 = P1 ^ 0;
sbit ADDR1 = P1 ^ 1;
sbit ADDR2 = P1 ^ 2;
sbit ADDR3 = P1 ^ 3;
sbit ENLED = P1 ^ 4;
sbit LED9 = P0 ^ 7;
sbit LED8 = P0 ^ 6;
sbit LED7 = P0 ^ 5;
sbit LED6 = P0 ^ 4;
sbit KEY1 = P2 ^ 4;
sbit KEY2 = P2 ^ 5;
sbit KEY3 = P2 ^ 6;
sbit KEY4 = P2 ^ 7;

void main() {
  ENLED = 0;  //选择独立LED进行显示
  ADDR3 = 1;
  ADDR2 = 1;
  ADDR1 = 1;
  ADDR0 = 0;
  P2 = 0xF7;  // P2.3置0，即KeyOut1输出低电平

  while (1) {
    //将按键扫描引脚的值传递到LED上
    LED9 = KEY1;  //按下时为0，对应的LED点亮
    LED8 = KEY2;
    LED7 = KEY3;
    LED6 = KEY4;
  }
}
