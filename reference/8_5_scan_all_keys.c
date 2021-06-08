/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：main.c
* 描  述：第8章 矩阵按键扫描并消抖的演示例程
* 版本号：v1.0.0
* 备  注：详情见第8章8.4.5节
*******************************************************************************
*/

#include <reg52.h>

sbit ADDR0 = P1 ^ 0;
sbit ADDR1 = P1 ^ 1;
sbit ADDR2 = P1 ^ 2;
sbit ADDR3 = P1 ^ 3;
sbit ENLED = P1 ^ 4;
sbit KEY_IN_1 = P2 ^ 4;
sbit KEY_IN_2 = P2 ^ 5;
sbit KEY_IN_3 = P2 ^ 6;
sbit KEY_IN_4 = P2 ^ 7;
sbit KEY_OUT_1 = P2 ^ 3;
sbit KEY_OUT_2 = P2 ^ 2;
sbit KEY_OUT_3 = P2 ^ 1;
sbit KEY_OUT_4 = P2 ^ 0;

unsigned char code LedChar[] = {  //数码管显示字符转换表
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
unsigned char KeySta[4][4] = {  //全部矩阵按键的当前状态
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {1, 1, 1, 1}};

void main() {
  unsigned char i, j;
  unsigned char backup[4][4] = {//按键值备份，保存前一次的值
                                {1, 1, 1, 1},
                                {1, 1, 1, 1},
                                {1, 1, 1, 1},
                                {1, 1, 1, 1}};

  EA = 1;     //使能总中断
  ENLED = 0;  //选择数码管DS1进行显示
  ADDR3 = 1;
  ADDR2 = 0;
  ADDR1 = 0;
  ADDR0 = 0;
  TMOD = 0x01;  //设置T0为模式1
  TH0 = 0xFC;   //为T0赋初值0xFC67，定时1ms
  TL0 = 0x67;
  ET0 = 1;          //使能T0中断
  TR0 = 1;          //启动T0
  P0 = LedChar[0];  //默认显示0

  while (1) {
    for (i = 0; i < 4; i++)  //循环检测4*4的矩阵按键
    {
      for (j = 0; j < 4; j++) {
        if (backup[i][j] != KeySta[i][j])  //检测按键动作
        {
          if (backup[i][j] != 0)  //按键按下时执行动作
          {
            P0 = LedChar[i * 4 + j];  //将编号显示到数码管
          }
        }
        backup[i][j] = KeySta[i][j];  //更新前一次的备份值
      }
    }
  }
}
/* T0中断服务函数，扫描矩阵按键状态并消抖 */
void InterruptTimer0() interrupt 1 {
  unsigned char i;
  static unsigned char keyout = 0;     //矩阵按键扫描输出索引
  static unsigned char keybuf[4][4] = {//矩阵按键扫描缓冲区
                                       {0xFF, 0xFF, 0xFF, 0xFF},
                                       {0xFF, 0xFF, 0xFF, 0xFF},
                                       {0xFF, 0xFF, 0xFF, 0xFF},
                                       {0xFF, 0xFF, 0xFF, 0xFF}};

  TH0 = 0xFC;  //重新加载初值
  TL0 = 0x67;
  //将一行的4个按键值移入缓冲区
  keybuf[keyout][0] = (keybuf[keyout][0] << 1) | KEY_IN_1;
  keybuf[keyout][1] = (keybuf[keyout][1] << 1) | KEY_IN_2;
  keybuf[keyout][2] = (keybuf[keyout][2] << 1) | KEY_IN_3;
  keybuf[keyout][3] = (keybuf[keyout][3] << 1) | KEY_IN_4;
  //消抖后更新按键状态
  for (i = 0; i < 4; i++)  //每行4个按键，所以循环4次
  {
    if ((keybuf[keyout][i] & 0x0F) ==
        0x00) {  //连续4次扫描值为0，即4*4ms内都是按下状态时，可认为按键已稳定的按下
      KeySta[keyout][i] = 0;
    } else if (
        (keybuf[keyout][i] & 0x0F) ==
        0x0F) {  //连续4次扫描值为1，即4*4ms内都是弹起状态时，可认为按键已稳定的弹起
      KeySta[keyout][i] = 1;
    }
  }
  //执行下一次的扫描输出
  keyout++;                //输出索引递增
  keyout = keyout & 0x03;  //索引值加到4即归零
  switch (keyout)  //根据索引，释放当前输出引脚，拉低下次的输出引脚
  {
    case 0:
      KEY_OUT_4 = 1;
      KEY_OUT_1 = 0;
      break;
    case 1:
      KEY_OUT_1 = 1;
      KEY_OUT_2 = 0;
      break;
    case 2:
      KEY_OUT_2 = 1;
      KEY_OUT_3 = 0;
      break;
    case 3:
      KEY_OUT_3 = 1;
      KEY_OUT_4 = 0;
      break;
    default:
      break;
  }
}
