/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：main.c
* 描  述：第6章 数码管动态显示原理示例(switch...case...语句示例)
* 版本号：v1.0.0
* 备  注：详情见第6章6.4节
*******************************************************************************
*/

#include <reg52.h>

sbit ADDR0 = P1 ^ 0;
sbit ADDR1 = P1 ^ 1;
sbit ADDR2 = P1 ^ 2;
sbit ADDR3 = P1 ^ 3;
sbit ENLED = P1 ^ 4;

unsigned char code LedChar[] = {  //数码管显示字符转换表
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
unsigned char LedBuff[6] = {  //数码管显示缓冲区，初值0xFF确保启动时都不亮
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void main() {
  unsigned char i = 0;    //动态扫描的索引
  unsigned int cnt = 0;   //记录T0中断次数
  unsigned long sec = 0;  //记录经过的秒数

  ENLED = 0;  //使能U3，选择控制数码管
  ADDR3 = 1;  //因为需要动态改变ADDR0-2的值，所以不需要再初始化了
  TMOD = 0x01;  //设置T0为模式1
  TH0 = 0xFC;   //为T0赋初值0xFC67，定时1ms
  TL0 = 0x67;
  TR0 = 1;  //启动T0

  while (1) {
    if (TF0 == 1)  //判断T0是否溢出
    {
      TF0 = 0;     // T0溢出后，清零中断标志
      TH0 = 0xFC;  //并重新赋初值
      TL0 = 0x67;
      cnt++;            //计数值自加1
      if (cnt >= 1000)  //判断T0溢出是否达到1000次
      {
        cnt = 0;  //达到1000次后计数值清零
        sec++;    //秒计数自加1
        //以下代码将sec按十进制位从低到高依次提取并转为数码管显示字符
        LedBuff[0] = LedChar[sec % 10];
        LedBuff[1] = LedChar[sec / 10 % 10];
        LedBuff[2] = LedChar[sec / 100 % 10];
        LedBuff[3] = LedChar[sec / 1000 % 10];
        LedBuff[4] = LedChar[sec / 10000 % 10];
        LedBuff[5] = LedChar[sec / 100000 % 10];
      }
      //以下代码完成数码管动态扫描刷新
      switch (i) {
        case 0:
          ADDR2 = 0;
          ADDR1 = 0;
          ADDR0 = 0;
          i++;
          P0 = LedBuff[0];
          break;
        case 1:
          ADDR2 = 0;
          ADDR1 = 0;
          ADDR0 = 1;
          i++;
          P0 = LedBuff[1];
          break;
        case 2:
          ADDR2 = 0;
          ADDR1 = 1;
          ADDR0 = 0;
          i++;
          P0 = LedBuff[2];
          break;
        case 3:
          ADDR2 = 0;
          ADDR1 = 1;
          ADDR0 = 1;
          i++;
          P0 = LedBuff[3];
          break;
        case 4:
          ADDR2 = 1;
          ADDR1 = 0;
          ADDR0 = 0;
          i++;
          P0 = LedBuff[4];
          break;
        case 5:
          ADDR2 = 1;
          ADDR1 = 0;
          ADDR0 = 1;
          i = 0;
          P0 = LedBuff[5];
          break;
        default:
          break;
      }
    }
  }
}
