/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：main.c
* 描  述：第8章 独立按键扫描并消抖的演示例程
* 版本号：v1.0.0
* 备  注：详情见第8章8.4.4节
*******************************************************************************
*/

#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit KEY1 = P2^4;
sbit KEY2 = P2^5;
sbit KEY3 = P2^6;
sbit KEY4 = P2^7;

unsigned char code LedChar[] = {  //数码管显示字符转换表
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};
bit KeySta = 1;  //当前按键状态

void main()
{
    bit backup = 1;  //按键值备份，保存前一次的扫描值
    unsigned char cnt = 0;  //按键计数，记录按键按下的次数
    
    EA = 1;       //使能总中断
    ENLED = 0;    //选择数码管DS1进行显示
    ADDR3 = 1;
    ADDR2 = 0;
    ADDR1 = 0;
    ADDR0 = 0;
    TMOD = 0x01;  //设置T0为模式1
    TH0  = 0xF8;  //为T0赋初值0xF8CD，定时2ms
    TL0  = 0xCD;
    ET0  = 1;     //使能T0中断
    TR0  = 1;     //启动T0
    P2 = 0xF7;    //P2.3置0，即KeyOut1输出低电平
    P0 = LedChar[cnt];   //显示按键次数初值
	
    while (1)
    {
        if (KeySta != backup)  //当前值与前次值不相等说明此时按键有动作
        {
            if (backup == 0)   //如果前次值为0，则说明当前是弹起动作
            {
                cnt++;         //按键次数+1
                if (cnt >= 10)
                {              //只用1个数码管显示，所以加到10就清零重新开始
                    cnt = 0;
                }
                P0 = LedChar[cnt];  //计数值显示到数码管上
            }
            backup = KeySta;   //更新备份为当前值，以备进行下次比较
        }
    }
}
/* T0中断服务函数，用于按键状态的扫描并消抖 */
void InterruptTimer0() interrupt 1
{
    static unsigned char keybuf = 0xFF;  //扫描缓冲区，保存一段时间内的扫描值
    
    TH0 = 0xF8;  //重新加载初值
    TL0 = 0xCD;
    keybuf = (keybuf<<1) | KEY4;  //缓冲区左移一位，并将当前扫描值移入最低位
    if (keybuf == 0x00)
    {   //连续8次扫描值都为0，即16ms内都只检测到按下状态时，可认为按键已按下
        KeySta = 0;
    }
    else if (keybuf == 0xFF)
    {   //连续8次扫描值都为1，即16ms内都只检测到弹起状态时，可认为按键已弹起
        KeySta = 1;
    }
    else
    {}  //其它情况则说明按键状态尚未稳定，则不对KeySta变量值进行更新
}
